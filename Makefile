CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include
SRCS = $(addprefix ./src/, ${SRCS_FILES})
SRCS_FILES = print/print.c \
scene/canvas.c \
scene/scene.c \
trace/ray.c \
utils/vec3_utils.c \
trace/hit/hit_sphere.c\
scene/object_create.c\
main.c
OBJS = $(SRCS:.c=.o)
NAME = miniRT

all : $(NAME)

%.o : %.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $^

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o ${NAME}
	@echo	"🙋‍♀️🙋‍♂️ make"

clean :
	@rm -rf $(OBJS)
	@echo	"🙋‍♀️🙋‍♂️ make clean"

fclean : clean
	@rm -rf $(NAME)
	@echo	"🙋‍♀️🙋‍♂️ make fclean"

re :
	@make fclean
	@make all
	@echo	"🙋‍♀️🙋‍♂️ make re"

.PHONY : all bonus clean fclean re