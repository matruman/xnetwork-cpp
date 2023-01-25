#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <iostream>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>

// Report a failure
void     fail(beast::error_code ec, char const* what);

// Return a reasonable mime type based on the extension of a file.
beast::string_view   mime_type(beast::string_view path);

#endif