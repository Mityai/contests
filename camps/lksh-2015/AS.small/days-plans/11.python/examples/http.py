import requests
f = open('a.html', 'w', encoding='utf-8')
r = requests.get('http://google.ru')
print(r)
print(r.text, file=f)
