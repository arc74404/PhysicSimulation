#include "new_form_object.hpp"

sml::NewFormObject::NewFormObject() : BaseObject(FormType::NEW)
{
}

bool
sml::NewFormObject::addBorder(BaseBorderPtr&& b)
{
    return BaseObject::addBorder(std::move(b));
}