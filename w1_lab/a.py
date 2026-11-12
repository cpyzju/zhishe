a = input()
b = input()
result = ''
carry = 0
i = 1
while i <= max(len(a), len(b)) or carry:
    digit_a = int(a[-i]) if i <= len(a) else 0
    digit_b = int(b[-i]) if i <= len(b) else 0
    total = digit_a+digit_b+carry
    result = str(total%10) + result
    carry = total//10
    i += 1
print(result)