#include <stdio.h>
#include <string.h>

void xorEncrypt(char *text, char *key) {
    int keyLen = strlen(key);
    for (int i = 0; text[i] != '\0'; i++) {
        text[i] ^= key[i % keyLen];
    }
}

int main() {
    char choice;
    printf("Enter 'e' to encrypt or 'd' to decrypt: ");
    scanf(" %c", &choice);

    if (choice == 'e') {
        char message[100];
        char filename[50];
        char key[20];

        printf("Enter the message to encrypt: ");
        fgets(message, sizeof(message), stdin);
        message[strcspn(message, "\n")] = '\0'; // Remove newline

        printf("Enter the filename to save encrypted data: ");
        scanf("%s", filename);

        printf("Enter the encryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "w");
        if (file == NULL) {
            perror("Error opening file for writing");
            return 1;
        }

        xorEncrypt(message, key);
        fprintf(file, "%s", message);
        fclose(file);
    } else if (choice == 'd') {
        char filename[50];
        char key[20];

        printf("Enter the filename to decrypt: ");
        scanf("%s", filename);

        printf("Enter the decryption key: ");
        scanf("%s", key);

        FILE *file = fopen(filename, "r");
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

        fread(encryptedData, sizeof(char), fileSize, file);
        encryptedData[fileSize] = '\0';
        fclose(file);

        xorEncrypt(encryptedData, key);

        printf("Decrypted message: %s\n", encryptedData);

        free(encryptedData);
    } else {
        printf("Invalid choice. Please enter 'e' or 'd'.\n");
    }

    return 0;
}