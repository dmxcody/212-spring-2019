import sys

tweets = []
with open(sys.argv[1]) as fid:
    for line in fid:
        tweets.append(line.strip().split('|'))

tweets = tweets[::-1]
n_tweets = len(tweets)
current = 0
while True:
    print tweets[current][1][:19] + '    ' + tweets[current][2]
    command = sys.stdin.readline().strip()
    if command == 'n':
        current = (current + 1) % n_tweets
    if command == 'p':
        current = current - 1 if (current > 0) else n_tweets - 1
    if command == 'f':
        current = 0
    if command == 'l':
        current = n_tweets - 1
    if command.isdigit():
        current = (current + int(command)) % n_tweets
    if command[0] == 's':
        words = command.split()
        for i in range(n_tweets):
            if words[1].lower() in tweets[(current+i+1)%n_tweets][2].lower():
                current = (current+i+1) % n_tweets
                break
    if (command == 'q'):
        break
