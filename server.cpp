#include <fstream>
#include <ctime>
#include <filesystem>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include "json.hpp"
#include "mongoose.h"
#include "tester.h"

static const char *s_listen_on = "http://0.0.0.0:8080";

static void handle_submit(struct mg_connection *c, struct mg_http_message *hm) {
    std::string body(hm->body.buf, hm->body.len);

    try {
        nlohmann::json j = nlohmann::json::parse(body);
        std::string tests_dir = j["tests_dir"];
        std::string code = j["code"];
        std::string result = run_tests_in_docker(code, tests_dir);
        mg_http_reply(c, 200, "Content-Type: text/plain\r\n", "%s", result.c_str());

    } catch (const std::exception &e) {
        mg_http_reply(c, 400, "", "JSON parse error: %s", e.what());
    }
}

void handle_request(struct mg_connection *c, int ev, void *ev_data) {
    if (ev == MG_EV_HTTP_MSG) {
        struct mg_http_message *hm = (struct mg_http_message *) ev_data;
        if (mg_match(hm->uri, mg_str("/submit"), NULL)) {
            handle_submit(c, hm);
        } else {
            struct mg_http_serve_opts opts = {.root_dir = "."};
            mg_http_serve_dir(c, hm, &opts);
        }
    }
}

int main() {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr);

    mg_http_listen(&mgr, s_listen_on, handle_request, NULL);
    printf("Сервер запущен на http://localhost:8080\n");

    for (;;) mg_mgr_poll(&mgr, 1000);

    mg_mgr_free(&mgr);
    return 0;
}