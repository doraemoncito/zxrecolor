#pragma once
#include <D3DTYPES.H>
#include <string>
#include <cassert>
#include <vector>

unsigned const TRANSPARENT_COLOR = RGB_MAKE(242, 10, 242);

class RcImage
{
public:
	unsigned Width, Height;
	std::vector<uint8_t> Data;
	std::vector<uint8_t> ZxMaskData;

	void LoadColored(const std::string& bmpName, bool convertZx = false, bool makeZxMask = false); // load 24-bit bmp
	void CopyWithShift(const RcImage& src_image, unsigned offset);
	bool IsFoundAt(unsigned char* curptr);
	void Blit(unsigned x, unsigned y, unsigned pitch, unsigned char* dst);
	unsigned short GetZxKey() const { return Data[0] * 256 + Data[Width / 8]; /* two first sprite lines */ }


private:
	struct PlainBMP
	{
		unsigned Width, Height;
		std::vector<uint8_t> Data;
		explicit PlainBMP(const std::string& bmpName);
	};

	static std::vector<uint8_t> convertToZx(const PlainBMP& bmp, bool asMask);

	void copyData(const RcImage& src_image, std::vector<uint8_t>& data);
	void shiftData(std::vector<uint8_t>& data);
};