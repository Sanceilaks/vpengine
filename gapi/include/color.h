#pragma once

class Color {
public:
	float R, G, B, A;

    Color() : R(1.f), G(1.f), B(1.f), A(1.f) {}
	Color(float r, float g, float b, float a = 1.f) : R(r), G(g), B(b), A(a) {}
	Color(float* arr) : R(arr[0]), G(arr[1]), B(arr[2]), A(arr[3]) {}
	Color(int r, int g, int b, int a = 255): R(r / 255.f), G(g / 255.f), B(b / 255.f), A(a / 255.f) {}

	void InitializeColor(float r, float g, float b, float a = 1.f) {
		R = r; G = g; B = b; A = a;
	}

	void InitializeColor(int r, int g, int b, int a = 255) {
		R = r / 255.f; G = g / 255.f; B = b / 255.f; A = a / 255.f;
	}

    void InitializeFromHSV(int h, int s, int v) {
        *this = FromHSV(h, s, v);
    }

	static Color FromHSV(int h, int s, int v) {
        double      hh, p, q, t, ff;
        long        i;

        Color out;

        if (s <= 0.0) {
            out.R = v;
            out.G = v;
            out.B = v ;
            return out;
        }
        hh = h;
        if (hh >= 360.0) hh = 0.0;
        hh /= 60.0;
        i = (long)hh;
        ff = hh - i;
        p = v * (1.0 - s);
        q = v * (1.0 - (s * ff));
        t = v * (1.0 - (s * (1.0 - ff)));

        switch (i) {
        case 0:
            out.R = v;
            out.G = t;
            out.B = p;
            break;
        case 1:
            out.R = q;
            out.G = v;
            out.B = p;
            break;
        case 2:
            out.R = p;
            out.G = v;
            out.B = t;
            break;

        case 3:
            out.R = p;
            out.G = q;
            out.B = v;
            break;
        case 4:
            out.R = t;
            out.G = p;
            out.B = v;
            break;
        case 5:
        default:
            out.R = v;
            out.G = p;
            out.B = q;
            break;
        }

        out.A = 1.f;
        return out;
	}
};