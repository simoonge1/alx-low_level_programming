#!/user/bin/python3

def largest_palindrome():
  largest_palindrome = 0
  for i in range(100, 1000):
    for j in range(100, 1000):
      product = i * j
      if str(product) == ''.join(reversed(str(product))) and product > largest_palindrome:
        largest_palindrome = product
  return largest_palindrome


# save the result in the file
with open("102-result", "w") as f:
  f.write(str(largest_palindrome()))
