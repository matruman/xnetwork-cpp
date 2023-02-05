#include "AbstractRoute.hpp"

AbstractRoute::AbstractRoute(ApplicationContext &context) : context(context) {}

ApplicationContext& AbstractRoute::getContext() const { return context; }