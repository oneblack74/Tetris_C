TARGET_EXEC ?= tetris

BUILD_DIR ?= build
SRC_DIRS ?= src

SRCS := src/controller/controller.c src/controller/sdlController.c src/main.c src/modele/modele.c src/view/sdlView.c src/view/view.c
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

CPPFLAGS ?= -MMD -MP -g -Isrc
LDFLAGS ?= $(shell sdl2-config --cflags --libs) -lm -lSDL2_image -lSDL2_mixer -lncurses


$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo Linking: "$@ ( $(foreach f,$^,$(subst $(BUILD_DIR)/$(SRC_DIRS),,$f)) )"	
	@$(CC) $(OBJS) -o $@ $(LDFLAGS)
	
$(BUILD_DIR)/%.c.o: %.c
	@echo Compiling: $<
	@$(MKDIR_P) $(dir $@)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
