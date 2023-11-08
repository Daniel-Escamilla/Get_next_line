SOURCE_FILES = 	

#	BONUS_FILE = 	

OBJECTS = $(SOURCE_FILES:.c=.o)

#	OBJECTS_BONUS = $(BONUS_FILE:.c=.o)

NAME = get_next_line.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME) : $(OBJECTS)
	ar -crs $@ $?

#	bonus: $(OBJECTS_BONUS)
#		ar -crs $(NAME) $?

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -rf $(OBJECTS)
#		rm -rf $(OBJECTS_BONUS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all