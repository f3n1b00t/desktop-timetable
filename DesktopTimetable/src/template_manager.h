#pragma once
#include "excel_template.h"

class template_manager
{
public:
    void add_template(const std::string& name, const excel_template& holder)
    {
        templates_.insert({ name, holder });
    }

    const excel_template& get_template(const std::string& name) const
    {
        return templates_.at(name);
    }

    void remove_template(const std::string& name)
    {
        templates_.erase(name);
    }

    const std::map<std::string, excel_template>& get_templates() const
    {
        return templates_;
    }

    static template_manager& get_instance()
    {
        static template_manager instance;
        return instance;
    }
private:
    std::map<std::string, excel_template> templates_;
};
