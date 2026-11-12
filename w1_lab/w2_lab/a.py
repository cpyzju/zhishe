stack = []
pairs = {')': '(', ']': '[', '}': '{'}
s = input().strip()
for ch in s:
    if ch in '([{':
        stack.append(ch)
    else:
        if not stack or stack[-1] != pairs[ch]:
            print(0)
            break
        stack.pop()
else:
    print(1)