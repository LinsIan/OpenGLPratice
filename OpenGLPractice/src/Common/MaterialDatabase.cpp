#include "MaterialDatabase.h"

std::string MaterialTypeToString(MaterialType type)
{
	switch (type)
	{
	case Emerald: return "Emerald";
	case Jade: return "Jade";
	case Obsidian: return "Obsidian";
	case Pearl: return "Pearl";
	case Ruby: return "Ruby";
	case Turquoise: return "Turquoise";
	case Brass: return "Brass";
	case Bronze: return "Bronze";
	case Chrome: return "Chrome";
	case Copper: return "Copper";
	case Gold: return "Gold";
	case Silver: return "Silver";
	case BlackPlastic: return "BlackPlastic";
	case CyanPlastic: return "CyanPlastic";
	case GreenPlastic: return "GreenPlastic";
	case RedPlastic: return "RedPlastic";
	case WhitePlastic: return "WhitePlastic";
	case YellowPlastic: return "YellowPlastic";
	case BlackRubber: return "BlackRubber";
	case CyanRubber: return "CyanRubber";
	case GreenRubber: return "GreenRubber";
	case RedRubber: return "RedRubber";
	case WhiteRubber: return "WhiteRubber";
	case YellowRubber: return "YellowRubber";
	default:
		return "";
	}
}

MaterialDatabase::MaterialDatabase()
{
	materialProperties[MaterialType::Emerald] = { {0.0215f, 0.1745f, 0.0215f}, {0.07568f, 0.61424f, 0.07568f}, {0.633f, 0.727811f, 0.633f}, 0.6f };
	materialProperties[MaterialType::Jade] = { {0.135f, 0.2225f, 0.1575f}, {0.54f, 0.89f, 0.63f}, {0.316228f, 0.316228f, 0.316228f}, 0.1f };
	materialProperties[MaterialType::Obsidian] = { {0.05375f, 0.05f, 0.06625f}, {0.1824f, 0.17f, 0.22525f}, {0.332741f, 0.328634f, 0.346435f}, 0.3f };
	materialProperties[MaterialType::Pearl] = { {0.25f, 0.20725f, 0.20725f}, {1.0f, 0.829f, 0.829f}, {0.296648f, 0.296648f, 0.296648f}, 0.088f };
	materialProperties[MaterialType::Ruby] = { {0.1745f, 0.01175f, 0.01175f}, {0.61424f, 0.04136f, 0.04136f}, {0.727811f, 0.626959f, 0.626959f}, 0.6f };
	materialProperties[MaterialType::Turquoise] = { {0.1f, 0.18725f, 0.1745f}, {0.396f, 0.74151f, 0.69102f}, {0.297254f, 0.30829f, 0.306678f}, 0.1f };
	materialProperties[MaterialType::Brass] = { {0.329412f, 0.223529f, 0.027451f}, {0.780392f, 0.568627f, 0.113725f}, {0.992157f, 0.941176f, 0.807843f}, 0.21794872f };
	materialProperties[MaterialType::Bronze] = { {0.2125f, 0.1275f, 0.054f}, {0.714f, 0.4284f, 0.18144f}, {0.393548f, 0.271906f, 0.166721f}, 0.2f };
	materialProperties[MaterialType::Chrome] = { {0.25f, 0.25f, 0.25f}, {0.4f, 0.4f, 0.4f}, {0.774597f, 0.774597f, 0.774597f}, 0.6f };
	materialProperties[MaterialType::Copper] = { {0.19125f, 0.0735f, 0.0225f}, {0.7038f, 0.27048f, 0.0828f}, {0.256777f, 0.137622f, 0.086014f}, 0.1f };
	materialProperties[MaterialType::Gold] = { {0.24725f, 0.1995f, 0.0745f}, {0.75164f, 0.60648f, 0.22648f}, {0.628281f, 0.555802f, 0.366065f}, 0.4f };
	materialProperties[MaterialType::Silver] = { {0.19225f, 0.19225f, 0.19225f}, {0.50754f, 0.50754f, 0.50754f}, {0.508273f, 0.508273f, 0.508273f}, 0.4f };
	materialProperties[MaterialType::BlackPlastic] = { {0.0f, 0.0f, 0.0f}, {0.01f, 0.01f, 0.01f}, {0.50f, 0.50f, 0.50f}, 0.25f };
	materialProperties[MaterialType::CyanPlastic] = { {0.0f, 0.1f, 0.06f}, {0.0f, 0.50980392f, 0.50980392f}, {0.50196078f, 0.50196078f, 0.50196078f}, 0.25f };
	materialProperties[MaterialType::GreenPlastic] = { {0.0f, 0.0f, 0.0f}, {0.1f, 0.35f, 0.1f}, {0.45f, 0.55f, 0.45f}, 0.25f };
	materialProperties[MaterialType::RedPlastic] = { {0.0f, 0.0f, 0.0f}, {0.5f, 0.0f, 0.0f}, {0.7f, 0.6f, 0.6f}, 0.25f };
	materialProperties[MaterialType::WhitePlastic] = { {0.0f, 0.0f, 0.0f}, {0.55f, 0.55f, 0.55f}, {0.70f, 0.70f, 0.70f}, 0.25f };
	materialProperties[MaterialType::YellowPlastic] = { {0.0f, 0.0f, 0.0f}, {0.5f, 0.5f, 0.0f}, {0.60f, 0.60f, 0.50f}, 0.25f };
	materialProperties[MaterialType::BlackRubber] = { {0.02f, 0.02f, 0.02f}, {0.01f, 0.01f, 0.01f}, {0.4f, 0.4f, 0.4f}, 0.078125f };
	materialProperties[MaterialType::CyanRubber] = { {0.0f, 0.05f, 0.05f}, {0.4f, 0.5f, 0.5f}, {0.04f, 0.7f, 0.7f}, 0.078125f };
	materialProperties[MaterialType::GreenRubber] = { {0.0f, 0.05f, 0.0f}, {0.4f, 0.5f, 0.4f}, {0.04f, 0.7f, 0.04f}, 0.078125f };
	materialProperties[MaterialType::RedRubber] = { {0.05f, 0.0f, 0.0f}, {0.5f, 0.4f, 0.4f}, {0.7f, 0.04f, 0.04f}, 0.078125f };
	materialProperties[MaterialType::WhiteRubber] = { {0.05f, 0.05f, 0.05f}, {0.5f, 0.5f, 0.5f}, {0.7f, 0.7f, 0.7f}, 0.078125f };
	materialProperties[MaterialType::YellowRubber] = { {0.05f, 0.05f, 0.0f}, {0.5f, 0.5f, 0.4f}, {0.7f, 0.7f, 0.04f}, 0.078125f };
}

MaterialDatabase::~MaterialDatabase()
{
}
