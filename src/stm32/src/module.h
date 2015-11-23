#ifndef _MODULE_H
#define _MODULE_H

/**
 *  Module struct
 */
typedef struct module {
	const char * name;
	void (*main_loop)(void);
	int (*config_handler)(const char* section, const char* name, const char* value);
} module_t;

/**
 * Register a module
 * @param mod Module to register
 * @return 0 if the module was registered without errors, a positive value on error
 */
int module_register(const module_t * mod);

/**
 * Call the module config_parser option
 * @param section Section name
 * @param name key name
 * @param value Value associated to the key
 * @return 1 if modules handled the parsed line, 0 if not
 */
int module_config_handler(const char* section, const char* name, const char* value);

/**
 * Call the module main loop functions
 */
void module_main_loop();

#endif
