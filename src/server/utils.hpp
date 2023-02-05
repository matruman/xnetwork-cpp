#ifndef UTILS_HPP
#define UTILS_HPP

#include <boost/beast/core.hpp>
#include <iostream>
#include <SQLAPI.h>

namespace beast = boost::beast;         // from <boost/beast.hpp>

// Report a failure
void     fail(beast::error_code ec, char const* what);

// Return a reasonable mime type based on the extension of a file.
beast::string_view  mime_type(beast::string_view path);

#endif