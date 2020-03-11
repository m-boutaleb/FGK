OGGETTI = FGK.o bufferManager.o decoding.o encoding.o tree.o fileManager.o
LIBRERIE = bufferManager.h decoding.h encoding.h tree.h fileManager.h
CC=gcc

%.o: %.c $(LIBRERIE)
	$(CC) -c -o $@ $<
FGK: $(OGGETTI)
	$(CC) -o $@ $^