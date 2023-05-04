CC = arch -x86_64 cc
CFLAGS = -Wall -Wextra -Werror
OPTION = -L./mlx -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I./include
SRCS = $(addprefix ./src/, ${SRCS_FILES})

SRCS_FILES = main.c \
print/print.c \
scene/canvas.c \
scene/scene.c \
scene/object_create.c \
trace/ray.c \
trace/hit/hit.c \
trace/hit/hit_sphere.c \
trace/hit/normal.c \
utils/vec3_utils.c \
utils/object_utils.c


OBJS = $(SRCS:.c=.o)
NAME = a.out

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OPTION) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $^ $(INCLUDES)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re :
	make fclean
	make all

.PHONY : all bonus clean fclean re