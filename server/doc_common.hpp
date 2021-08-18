#pragma once

namespace scymnus {

enum ParameterType { Body, Path, Header, Query, Form, Segment };

template <int c> constexpr const char *http_status_description() {
    switch (c) {
    case 100:
        return "Continue";
    case 101:
        return "Switching Protocols";
    case 102:
        return "Processing";
    case 200:
        return "OK";
    case 201:
        return "Created";
    case 202:
        return "Accepted";
    case 203:
        return "Non-Authoritative Information";
    case 204:
        return "No Content";
    case 205:
        return "Reset Content";
    case 206:
        return "Partial Content";
    case 207:
        return "Multi-Status";
    case 208:
        return "Already Reported";
    case 226:
        return "IM Used";
    case 300:
        return "Multiple Choices";
    case 301:
        return "Moved Permanently";
    case 302:
        return "Found";
    case 303:
        return "See Other";
    case 304:
        return "Not Modified";
    case 305:
        return "Use Proxy";
    case 307:
        return "Temporary Redirect";
    case 308:
        return "Permanent Redirect";
    case 400:
        return "Bad Request";
    case 401:
        return "Unauthorized";
    case 402:
        return "Payment Required";
    case 403:
        return "Forbidden";
    case 404:
        return "Not Found";
    case 405:
        return "Method Not Allowed";
    case 406:
        return "Not Acceptable";
    case 407:
        return "Proxy Authentication Required";
    case 408:
        return "Request Timeout";
    case 409:
        return "Conflict";
    case 410:
        return "Gone";
    case 411:
        return "Length Required";
    case 412:
        return "Precondition Failed";
    case 413:
        return "Request Entity Too Large";
    case 414:
        return "Request-URI Too Long";
    case 415:
        return "Unsupported Media Type";
    case 416:
        return "Requested Range Not Satisfiable";
    case 417:
        return "Expectation Failed";
    case 422:
        return "Unprocessable Entity";
    case 423:
        return "Locked";
    case 424:
        return "Failed Dependency";
    case 426:
        return "Upgrade Required";
    case 428:
        return "Precondition Required";
    case 429:
        return "Too Many Requests";
    case 431:
        return "Request Header Fields Too Large";
    case 444:
        return "No Response";
    case 500:
        return "Internal Server Error";
    case 501:
        return "Not Implemented";
    case 502:
        return "Bad Gateway";
    case 503:
        return "Service Unavailable";
    case 504:
        return "Gateway Timeout";
    case 505:
        return "HTTP Version Not Supported";
    case 506:
        return "Variant Also Negotiates";
    case 507:
        return "Insufficient Storage";
    case 508:
        return "Loop Detected";
    case 509:
        return "Bandwidth Limit Exceeded";
    case 510:
        return "Not Extended";
    case 511:
        return "Network Authentication Required";
    case 598:
        return "Network read timeout error";
    case 599:
        return "Network connect timeout error";
    default:
        return "";
    }
}

} // namespace scymnus
