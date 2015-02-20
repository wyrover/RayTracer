/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
*
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#pragma once

struct Colour
{
	Colour()
	{
		// Set default values
		red = green = blue = 0;
	}

	// My additional functions - for ease of adding/multiplying/scaling colours

	const Colour operator+(const Colour &rhs) const
	{
		Colour result;

		result.red = red + rhs.red;
		result.green = green + rhs.green;
		result.blue = blue + rhs.blue;

		return result;
	}

	const void operator+=(const Colour &rhs)
	{
		red += rhs.red;
		green += rhs.green;
		blue += rhs.blue;
	}

	const void operator=(const Colour &rhs)
	{
		red = rhs.red;
		green = rhs.green;
		blue = rhs.blue;
	}

	const Colour operator*(const Colour &rhs) const
	{
		Colour result;

		result.red = red * rhs.red;
		result.green = green * rhs.green;
		result.blue = blue * rhs.blue;

		return result;
	}

	const void operator*=(const Colour &rhs)
	{
		red *= rhs.red;
		green *= rhs.green;
		blue *= rhs.blue;
	}

	const Colour operator*(const float scaler) const
	{
		Colour result;

		result.red = red * scaler;
		result.green = green * scaler;
		result.blue = blue * scaler;

		return result;
	}

	const void operator*=(const float scaler)
	{
		red *= scaler;
		green *= scaler;
		blue *= scaler;
	}

	float red;
	float green;
	float blue;
};

class Material
{
	private:
		Colour m_ambient;
		Colour m_diffuse;
		Colour m_specular;
		double m_specpower;
		bool m_castShadow;

		double m_refractiveIndex;

	public:
		
		Material();
		~Material();

		void SetDefaultMaterial();
		void SetAmbientColour(float r, float g, float b);
		void SetDiffuseColour(float r, float g, float b);
		void SetSpecularColour(float r, float g, float b);
		void SetSpecPower(double spow);

		inline void SetCastShadow(bool castShadow)
		{
			m_castShadow = castShadow;
		}

		inline Colour GetAmbientColour()
		{
			return m_ambient;
		}
		
		inline Colour GetDiffuseColour()
		{
			return m_diffuse;
		}

		inline Colour GetSpecularColour()
		{
			return m_specular;
		}

		inline double GetSpecPower()
		{
			return m_specpower;
		}

		inline bool CastShadow()
		{
			return m_castShadow;
		}

		// My additional functions

		inline void SetRefractiveIndex(double r)
		{
			m_refractiveIndex = r;
		}

		inline double GetRefractiveIndex()
		{
			return m_refractiveIndex;
		}
};

