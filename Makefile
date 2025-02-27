CFLAGS = -Wall -Wextra -Werror
LFLAGS = -lbsd -lX11 -lm -lXext
CC = cc
AR = ar
ARFLAG = -rcs
MAKE := $(MAKE) -j

GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
RED    = \033[31m
RESET  = \033[0m

CFILE =	main.c

FILE =	main.c check_map.c map_parsing.c pathing.c drawing.c input.c setting.c \
		event.c loading.c setting_change.c game_loop.c color_util.c

LIB_D = libft/

MLX_D = minilibx-linux/

LIB = $(LIB_D)libft.a $(MLX_D)libmlx.a $(MLX_D)libmlx_Linux.a

CSRCDIR = src_bonus/

SRCDIR = src/

SRCS = $(SRCDIR)$(FILE)

INCDIR = inc/

INC = so_long.h

OBJDIR = .Obj/

OBJS = $(FILE:%.c=$(OBJDIR)%.o)

NAME = so_long

all: $(NAME) Makefile

$(NAME) : $(OBJS)
	@echo "$(YELLOW)Creating final product : $(BLUE)$@...$(RESET)"
	@$(CC) $(CFLAGS) $(LFLAGS) $^ $(LIB) -o $@ && echo "$(GREEN)$@ Created successfully !$(RESET)"

$(OBJDIR)%.o: $(SRCDIR)%.c $(LIB) $(INCDIR)$(INC) | $(OBJDIR)
	$(CC) -c $(CFLAGS) -I $(INCDIR) -I $(MLX_D) -I $(LIB_D)$(INCDIR) $< -o $@

$(OBJDIR):
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling...$(RESET)"

$(LIB): FORCE
	@$(MAKE) -C $(LIB_D) --no-print-directory
	@$(MAKE) -C $(MLX_D) --no-print-directory


clean:
	@echo "$(RED)Deleting object files...$(RESET)"
	@rm -rf $(OBJDIR) && echo "$(GREEN)Done !$(RESET)"
	@$(MAKE) $@ -C $(LIB_D) --no-print-directory
	@$(MAKE) $@ -C $(MLX_D) --no-print-directory
	
fclean: clean
	@echo "$(RED)Deleting executable or library $(NAME)...$(RESET)"
	@rm -f $(NAME) && echo "$(GREEN)Done !$(RESET)"
	@$(MAKE) $@ -C $(LIB_D) --no-print-directory
	
re: fclean all

FORCE:

.PHONY: clean fclean re all bonus