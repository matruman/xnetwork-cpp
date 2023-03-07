#include "AbstractRoute.hpp"

AbstractRoute::AbstractRoute(std::shared_ptr<ApplicationContext> context) : context(context) {}

ApplicationContext& AbstractRoute::getContext() { return *context; }