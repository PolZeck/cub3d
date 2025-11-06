# **************************************************************************** #
#                                   cub3D                                       #
# **************************************************************************** #

# === Project ===
NAME        := cub3D

# === Dossiers ===
SRC_DIR     := src
INC_DIR     := inc
OBJ_DIR     := obj
DEPS_DIR    := dep
LIBFT_DIR   := libft
MLX_DIR     := minilibx-linux

# === Compiler / Flags ===
CC          := cc
CFLAGS      := -Wall -Wextra -Werror
CPPFLAGS    := -I$(INC_DIR)
LDFLAGS     :=

# === libft ===
LIBFT_A     := $(LIBFT_DIR)/libft.a
# adapte si besoin (racine vs includes/)
LIBFT_INC   := -I$(LIBFT_DIR)
LIBFT_LNK   := -L$(LIBFT_DIR) -lft

# === MiniLibX (Linux) ===
MLX_A       := $(MLX_DIR)/libmlx.a
MLX_INC     := -I$(MLX_DIR)
MLX_LNK     := -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Ajout des includes de libs
CPPFLAGS    += $(LIBFT_INC) $(MLX_INC)

# === SOURCES ===
SRCS := \
	main.c \
	parsing/parse.c \
	parsing/parse_textures.c \
	parsing/parse_map.c \
	parsing/check_map.c \
	parsing/parse_colors.c \
	parsing/str_utils.c \
	parsing/normalize_map_utils.c \
	parsing/check_map_closed.c \
	app/hooks.c \
	app/init.c \
	app/textures.c \
	app/window.c \
	app/draw.c \
	app/mouse.c \
	parsing/parse_config_utils.c \
	app/controls.c \
	app/movements.c \
	raycast/render.c \
	raycast/ray_intersect.c \
	raycast/ray_post.c \
	raycast/ray_setup.c \
	raycast/texturemap.c \
	raycast/get_text.c \
	raycast/ray_box_intersect.c \
	utils/free.c \
	utils/errors.c \
	utils/utils.c \
	minimap/minimap.c \
	minimap/minimap_utils.c

SRCS_BONUS :=

# === Transformations ===
OBJS       := $(SRCS:%.c=$(OBJ_DIR)/%.o)
DEPS       := $(SRCS:%.c=$(DEPS_DIR)/%.d)

OBJS_BONUS := $(SRCS_BONUS:%.c=$(OBJ_DIR)/%.o)
DEPS_BONUS := $(SRCS_BONUS:%.c=$(DEPS_DIR)/%.d)

# === Couleurs ===
COLOR_OK   := \033[1;32m
COLOR_INFO := \033[1;36m
COLOR_WARN := \033[1;33m
COLOR_ERR  := \033[1;31m
COLOR_RST  := \033[0m

# === Phony ===
.PHONY: all clean fclean re bonus print help libft mlx

# === Default ===
all: $(NAME)

# === Build libs  ===
libft:
	@printf "$(COLOR_INFO)[LIBFT]$(COLOR_RST) make -C $(LIBFT_DIR)\n"
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR)

mlx:
	@printf "$(COLOR_INFO)[MLX ]$(COLOR_RST) make -C $(MLX_DIR)\n"
	@$(MAKE) --no-print-directory -C $(MLX_DIR)
# === Link ===
$(NAME): libft mlx $(OBJS)
	@printf "$(COLOR_INFO)[LD  ]$(COLOR_RST) $@\n"
	@$(CC) $(LDFLAGS) $(OBJS) $(LIBFT_LNK) $(MLX_LNK) -o $@
	@printf "$(COLOR_OK)[OK  ]$(COLOR_RST) Built $(NAME)\n"

# === Bonus ===
bonus: CFLAGS += -DBONUS=1
bonus: libft mlx $(OBJS_BONUS)
	@printf "$(COLOR_INFO)[LD  ]$(COLOR_RST) $@\n"
	@$(CC) $(LDFLAGS) $(OBJS_BONUS) $(LIBFT_LNK) $(MLX_LNK) -o $(NAME)
	@printf "$(COLOR_OK)[OK  ]$(COLOR_RST) Built $(NAME) (bonus)\n"

# === Compile rule ===
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@) $(DEPS_DIR)/$(dir $*)
	@printf "$(COLOR_INFO)[CC  ]$(COLOR_RST) $<\n"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@ \
		-MMD -MP -MF $(DEPS_DIR)/$*.d

# === Clean ===
clean:
	@printf "$(COLOR_INFO)[CLEAN]$(COLOR_RST) remove objects & deps\n"
	@rm -rf $(OBJ_DIR) $(DEPS_DIR)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean || true
	@$(MAKE) --no-print-directory -C $(MLX_DIR) clean || true

fclean: clean
	@printf "$(COLOR_INFO)[FCLEAN]$(COLOR_RST) remove binary\n"
	@rm -f $(NAME)
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean || true

re: fclean all

# === Debug ===
print:
	@echo "SRC_DIR    : $(SRC_DIR)"
	@echo "SRCS       : $(SRCS)"
	@echo "OBJS       : $(OBJS)"
	@echo "DEPS       : $(DEPS)"

help:
	@echo "Targets: all | bonus | clean | fclean | re | print"

# === Include deps ===
-include $(DEPS) $(DEPS_BONUS)
