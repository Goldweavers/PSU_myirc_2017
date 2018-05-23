/*
** EPITECH PROJECT, 2021
** PSU_myirc_2017
** File description:
**
*/


char *generate_nickname()
{
	char *nickname = calloc(10, sizeof(char));
	user_t *user = server.users.data;

	sprintf(nickname, "guest%d", rand() % (9999 - 1000 + 1) + 1000);
	for (user_t *user = server.users.data; user != NULL; user =
		user->next) {
		if (strcmp(user->nickname, nickname) != 0)
			return generate_nickname();
	}
	return nickname;
}
