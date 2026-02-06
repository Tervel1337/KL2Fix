#include "FileLoader.h"
const char* PatchArchive = "KL2FixPatch01.zip";

void FileLoader::Install() {
	Patch<const char*>(0x007F5611, PatchArchive);
}