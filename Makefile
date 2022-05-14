NAME	= cont
NAME_ST = cont_std
NAME_COMP = comp

CXX		= clang++
FLAGS	= -Wall -Wextra -Werror -std=c++98 -g
FLAGS1	= -Wall -Wextra -Werror -std=c++98 -DSTD
SRC_DIR	= ./
OBJ_DIR	= objs/

FILES	= tests
SRCS 	= $(patsubst %, $(SRC_DIR)%.cpp, $(FILES))
OBJS 	= $(patsubst %, $(OBJ_DIR)%.o, $(FILES))
OBJS1 	= $(patsubst %, $(OBJ_DIR)%1.o, $(FILES))


all: $(NAME) $(NAME_ST)

my: $(NAME)

std: $(NAME_ST)

comp: compare_res.cpp

test: all
	./cont > my.txt
	./cont_std > orig.txt
	./comp


$(NAME): $(OBJS)
	$(CXX) -o $(NAME) $(FLAGS) $(OBJS)

$(NAME_ST): $(OBJS1)
	$(CXX) -o $(NAME_ST) $(FLAGS1) $(OBJS1)


$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS) -c $< -o $@

$(OBJ_DIR)%1.o: $(SRC_DIR)%.cpp
	mkdir -p $(OBJ_DIR)
	$(CXX) $(FLAGS1) -c $< -o $@

$(NAME_COMP):
	$(CXX) compare_res.cpp -o $(NAME_COMP)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME_ST)
	rm -f $(NAME_COMP)
	rm -f $(NAME)
	rm -f my.txt
	rm -f orig.txt

re: fclean all comp

.PHONY: all clean fclean re