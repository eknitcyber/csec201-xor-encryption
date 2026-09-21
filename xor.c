#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void xorEncrypt(char *text, int length, char *key) {
    int keyLen = strlen(key);

    for (int i = 0; i < length; i++) {
        text[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice;
    printf("Enter 'e' to encrypt or 'd' to decrypt: ");
    scanf(" %c", &choice);
    getchar();

    if (choice == 'e') {
        char message[100];
        char filename[50];
        char key[20];

        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0';

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "wb");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        int messageLength = strlen(message);
        xorEncrypt(message,messageLength, key);
        fwrite(message, sizeof(char), messageLength, file);
        fclose(file);

    } else if (choice == 'd') {
        char filename[50];
        char key[20];

        printf("Enter the filename to decrypt: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "rb");
        if (file == NULL) {
            perror("Error opening file for reading");
            return 1;
        }

        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        char *encryptedData = (char *)malloc(fileSize + 1);
        if (encryptedData == NULL) {
            perror("Error allocating memory");
            fclose(file);
            return 1;
        }

        fread(encryptedData, 1, fileSize, file);
        fclose(file);
        xorEncrypt(encryptedData, fileSize, key);
        printf("Decrypted message: %.*s\n", (int)fileSize, encryptedData);

        free(encryptedData);
    } else {
        printf("Invalid choice. Please enter 'e' or 'd'.\n");
    }

    return 0;
}