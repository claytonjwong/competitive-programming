#python2

def main():
    n, k = map(int, raw_input().split());
    a = [map(int, raw_input().split()) for _ in xrange(n)]
    s = [[0] * (n + 1) for _ in xrange(n + 1)]
    result = 0
    for i in xrange(n):
        for j in xrange(n):
            s[i + 1][j + 1] = a[i][j] + s[i][j + 1] + s[i + 1][j] - s[i][j]
            if i + 1 >= k and j + 1 >= k:
                result = max(result, s[i + 1][j + 1] + s[i + 1 - k][j + 1 - k] - s[i + 1 - k][j + 1] - s[i + 1][j + 1 - k])
    
    print result
    
    
if __name__ == '__main__':
    main()
    