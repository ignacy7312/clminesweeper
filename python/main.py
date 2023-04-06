import random
from termcolor import colored
import re

class Board:
    def __init__(self, dim_size, num_bombs):
        # parameters
        self.dim_size = dim_size
        self.num_bombs = num_bombs

        # create the board
        self.board = self.make_new_board()
        self.assign_values_to_board()

        self.dug = set()

    
    def __str__(self):
        visible_board = [[None for _ in range(self.dim_size)] for _ in range(self.dim_size)]
        final_string = ' ' + ''.join([f' {i}' for i in range(self.dim_size)]) + '\n'
        
        for row in range(self.dim_size):
            final_string += f'{row} '
            for col in range(self.dim_size):
                if (row,col) in self.dug:
                    visible_board[row][col] = str(self.board[row][col])
                else:
                    visible_board[row][col] = ' '
                final_string += visible_board[row][col] + ' '
            final_string += '\n'
        
        return final_string


    def make_new_board(self):
        board = [[None for _ in range(self.dim_size)] for _ in range(self.dim_size)]
        bombs_planted = 0
        while bombs_planted < self.num_bombs:
            x, y = random.randint(0, self.dim_size - 1), random.randint(0, self.dim_size - 1)
            if board[x][y] == '*':
                continue
            
            board[x][y] = '*'
            bombs_planted += 1
        
        return board

    def assign_values_to_board(self):
        for r in range(self.dim_size):
            for c in range(self.dim_size):
                if self.board[r][c] == '*':
                    continue

                self.board[r][c] = self.get_num_neighboring_bombs(r,c)



    def get_num_neighboring_bombs(self, row, col):
        bomb_count = 0
        for x in range(-1, 2):
            for y in range(-1, 2):
                if x == y == 0 or row + x < 0 or col + y < 0:
                    continue

                try:
                    if self.board[row + x][col + y] == '*':
                        bomb_count += 1
                except:
                    IndexError()
                    continue
        """
        for x in range(max(0, row - 1), min(self.dim_size - 1, (row + 1)) + 1):
            for y in range(max(0, col - 1), min(self.dim_size - 1, (col + 1)) + 1):
                if x == row and y == col:
                    continue
                if self.board[x][y] == '*':
                    bomb_count += 1"""
        return bomb_count


    def dig(self, row, col):
       
        self.dug.add((row,col))

        # hit a bomb
        if self.board[row][col] == '*':
            return False
        
        # neighboring bombs
        if self.board[row][col] > 0:
            return True

        # no bombs nearby self.board[row][col] == 0
        # check for neighbors
        
        """for x in range(-1, 2):
            for y in range(-1, 2):

                if row + x < 0 or row + x >= self.dim_size or col + y < 0 or col + y >= self.dim_size:
                    continue
                if (row + x, col + y) in self.dug:
                    continue

                self.dig(row+ x, row + y)"""
        
        for x in range(max(0, row - 1), min(self.dim_size - 1, (row + 1)) + 1):
            for y in range(max(0, col - 1), min(self.dim_size - 1, (col + 1)) + 1):
                if (x,y) in self.dug:
                    continue
                self.dig(x,y)

        return True




    def print_board(self):
        for i in range(self.dim_size - 1):
            for j in range(self.dim_size - 1):
                #spot = self.board[i][j]
                #if spot == '*': print(colored(spot 'red')) print(self.board[i][j], end=' ')
                print(self.board[i][j], end=' ')
            print() 


# play the game
def play(dim_size=10, num_bombs=10):
    # 1. create the board and plant the bombs
    board = Board(dim_size, num_bombs)
    # 2. show the user the board and ask where to dig

    # 3a. if location is a bomb, game over


    # 3b. if not a bomb, dig recursively until each swqure is at  least next to a bomb
    # 4. repeat 2/3 until no more places to dig -> until victory
    safe = True
    
    while(len(board.dug) < board.dim_size**2 - num_bombs):
        print(board)
        user_input = re.split(',(\\s)*', input("Where would you like to dig? Input as row,col: "))
        row, col = int(user_input[0]), int(user_input[-1])
        
        if row < 0 or row >= board.dim_size or col < 0 or col >= dim_size:
            print("Invalid location, try again")    
            continue
        
        safe = board.dig(row, col)

        if not safe: 
            # dug a bomb - game over 
            break

    
    if safe:
        print("Congratulations You won")
    else:
        print("Sorry game over")
        board.dug = [(r,c) for r in range(board.dim_size) for c in range(board.dim_size)]
        print(board)

if __name__ == "__main__":
    play()