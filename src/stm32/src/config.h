#ifndef _CONFIG_H
#define _CONFIG_H

/**
 * Initialize config system
 * @note This function should be called first to allow system to get values
 */
void config_init();

/**
 * Get a config value as a string
 * @param[in] str String key to get value from
 * @param[out] Buffer to store the string
 * @param Length of the buffer
 * @return 0 on success, a positive value on erro
 */
int config_get_str(const char *str, char *value, unsigned int len);

/**
 * Get a config value as a string
 * @param[in] str String key to get value from
 * @param[out] Buffer to store the int
 * @param Length of the buffer
 * @return 0 on success, a positive value on erro
 */
int config_get_int(const char *str, int *value);

#endif
