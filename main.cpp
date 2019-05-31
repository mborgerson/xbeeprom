
// TODO: Make this more useful. I just needed to set the MAC
// address at time of writing, but there's a lot more that
// could be useful.

#include "XKEEPROM.h"
#include <stdio.h>
#include <string.h>

const char *usage = "%s <eeprom file> <new mac address>\n";

int main(int argc, char *argv[])
{
	if (argc < 2) {
		fprintf(stderr, usage, argv[0]);
		return 1;
	}

	const char *eeprom_path = argv[1];
	FILE *fd = fopen(eeprom_path, "rb");
	if (fd == NULL) {
		fprintf(stderr, "Failed to open eeprom file\n");
		return 1;
	}

	fseek(fd, 0, SEEK_END);
	size_t eeprom_size = ftell(fd);

	if (eeprom_size != 256) {
		fprintf(stderr, "Expected 256 byte eeprem, got %zd\n", eeprom_size);
		return 1;
	}
	fseek(fd, 0, SEEK_SET);

	EEPROMDATA eeprom_data;
	size_t bytes_read = fread(&eeprom_data, 1, 256, fd);
	assert(bytes_read == eeprom_size);
	fclose(fd);

	XKEEPROM eeprom(&eeprom_data, TRUE);
	// eeprom.Decrypt();

	char buf[64];
	DWORD len;
	eeprom.GetMACAddressString(buf, &len);
	printf("MAC Address: %s\n", buf);

	if (argc < 3) return 0;

	char *new_mac = argv[2];
	printf("Setting MAC address to %s\n", new_mac);
	eeprom.SetMACAddressString(new_mac);

	BOOL result = eeprom.EncryptAndCalculateCRC();
	eeprom.GetEEPROMData(&eeprom_data);

	fd = fopen(eeprom_path, "wb");
	if (fd == NULL) {
		fprintf(stderr, "Failed to open eeprom file\n");
		return 1;
	}
	size_t bytes_written = fwrite(&eeprom_data, 1, 256, fd);
	assert(bytes_written == 256);
	fclose(fd);

	printf("Ok\n");
	return 0;
}
