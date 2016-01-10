#ifndef _CONFIG_H
#define _CONFIG_H

#include "json.h"

/**
 * Initialize config system
 * @note This function should be called first to allow system to get values
 */
void
config_init();

json_value *
config_get_section(json_value *json, const char *section_name);

#endif
