import sys

def generate_bayer_matrix(n):
    n = int(n)
    if n % 2 != 0:
        raise ValueError("Bayer matrix size must be even")
    
    def recurse_bayer(size, offset):
        if size == 1:
            return [[0]]
        
        smaller = recurse_bayer(size // 2, offset)
        
        upper_left = [[(2 * x + y) % (size * size) for x in row] for y, row in enumerate(smaller)]
        lower_right = [[(2 * x + y + offset) % (size * size) for x in row] for y, row in enumerate(smaller)]
        upper_right = [[(2 * x + y + 3 * size) % (size * size) for x in row] for y, row in enumerate(smaller)]
        lower_left = [[(2 * x + y + 2 * size) % (size * size) for x in row] for y, row in enumerate(smaller)]
        
        return [a + b for a, b in zip(upper_left, upper_right)] + [a + b for a, b in zip(lower_left, lower_right)]
    
    bayer_matrix = recurse_bayer(n, 0)
    bayer = [cell for row in bayer_matrix for cell in row]
    
    return bayer

def main():
    if len(sys.argv) < 2:
        print("Error -- Usage: python generate_bayer_matrix.py <matrix_dim>")
        sys.exit(1)

    n = sys.argv[1]
    
    bayer = generate_bayer_matrix(n)
    print(bayer)

if __name__ == "__main__":
    main()

    