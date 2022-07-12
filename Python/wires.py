num = int(input()) #Arrays length

triangleConnectors = sorted(list(map(int, input().split())))
circleConnectors = sorted(list(map(int, input().split())), reverse=True)

length = 0

for i in range(num):
    length += abs(triangleConnectors[i] - circleConnectors[i])

print(length)