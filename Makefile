NAME=bfc

CC=gcc
CFLAGS=-Wall -Wextra -Werror

HEADER_FOLDER=./includes
SOURCES_FOLDER=srcs
OBJ_FOLDER=out

SOURCES=$(shell find $(SOURCES_FOLDER) -type f -name '*.c')
OUT=$(addprefix $(OBJ_FOLDER)/,$(notdir $(SOURCES:.c=.o)))

INCLUDE_PATH=-I $(HEADER_FOLDER)

all: $(NAME)

$(NAME): $(OUT)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -o $(NAME) $(OUT)

$(OBJ_FOLDER)/%.o: $(SOURCES_FOLDER)/%.c
	@mkdir -p $(OBJ_FOLDER)
	$(CC) $(CFLAGS) $(INCLUDE_PATH) -o $@ -c $<

clean:
	rm -rf $(OBJ_FOLDER)

fclean: clean
	rm -f $(NAME)

re: fclean all