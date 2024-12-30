#include "new_form_object.hpp"

sml::NewFormObject::NewFormObject() : BaseObject(FormType::NEW)
{
}

void
sml::NewFormObject::addBorder(BaseBorderPtr&& b)
{
    BaseObject::addBorder(std::move(b));
}