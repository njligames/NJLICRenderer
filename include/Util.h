//
//  Util.h
//
//  Created by James Folk on 1/17/22.
//  Copyright © 2016 NJLICGames Ltd. All rights reserved.
//

#ifndef Util_h
#define Util_h

#include "GraphicsPlatform.h"

#include "SDL.h"
#include <algorithm>
#include <cctype>
#include <optional>
#include <regex>
#include <stdexcept>
#include <string>

#include "glm/glm.hpp"

#define FORMATSTRING_MAT4x4                                                    \
    "{\"glm::mat4x4\":[{\"xx\":\"%f\", \"xy\":\"%f\", \"xz\":\"%f\", "         \
    "\"xw\":\"%f\", \"yx\":\"%f\", \"yy\":\"%f\", \"yz\":\"%f\", "             \
    "\"yw\":\"%f\", \"zx\":\"%f\", \"zy\":\"%f\", \"zz\":\"%f\", "             \
    "\"zw\":\"%f\", \"wx\":\"%f\", \"wy\":\"%f\", \"wz\":\"%f\", "             \
    "\"ww\":\"%f\"}]}"




class Util {
public:
    enum class Color {
        AIR_FORCE_BLUE_RAF=0,
        AIR_FORCE_BLUE_USAF,
        AIR_SUPERIORITY_BLUE,
        ALABAMA_CRIMSON,
        ALICE_BLUE,
        ALIZARIN_CRIMSON,
        ALLOY_ORANGE,
        ALMOND,
        AMARANTH,
        AMBER,
        AMBER_SAE_ECE,
        AMERICAN_ROSE,
        AMETHYST,
        ANDROID_GREEN,
        ANTI_FLASH_WHITE,
        ANTIQUE_BRASS,
        ANTIQUE_FUCHSIA,
        ANTIQUE_RUBY,
        ANTIQUE_WHITE,
        AO_ENGLISH,
        APPLE_GREEN,
        APRICOT,
        AQUA,
        AQUAMARINE,
        ARMY_GREEN,
        ARSENIC,
        ARYLIDE_YELLOW,
        ASH_GREY,
        ASPARAGUS,
        ATOMIC_TANGERINE,
        AUBURN,
        AUREOLIN,
        AUROMETALSAURUS,
        AVOCADO,
        AZURE,
        AZURE_MIST_WEB,
        BABY_BLUE,
        BABY_BLUE_EYES,
        BABY_PINK,
        BALL_BLUE,
        BANANA_MANIA,
        BANANA_YELLOW,
        BARN_RED,
        BATTLESHIP_GREY,
        BAZAAR,
        BEAU_BLUE,
        BEAVER,
        BEIGE,
        BIG_DIP_O_RUBY,
        BISQUE,
        BISTRE,
        BITTERSWEET,
        BITTERSWEET_SHIMMER,
        BLACK,
        BLACK_BEAN,
        BLACK_LEATHER_JACKET,
        BLACK_OLIVE,
        BLANCHED_ALMOND,
        BLAST_OFF_BRONZE,
        BLEU_DE_FRANCE,
        BLIZZARD_BLUE,
        BLOND,
        BLUE,
        BLUE_BELL,
        BLUE_CRAYOLA,
        BLUE_GRAY,
        BLUE_GREEN,
        BLUE_MUNSELL,
        BLUE_NCS,
        BLUE_PIGMENT,
        BLUE_RYB,
        BLUE_SAPPHIRE,
        BLUE_VIOLET,
        BLUSH,
        BOLE,
        BONDI_BLUE,
        BONE,
        BOSTON_UNIVERSITY_RED,
        BOTTLE_GREEN,
        BOYSENBERRY,
        BRANDEIS_BLUE,
        BRASS,
        BRICK_RED,
        BRIGHT_CERULEAN,
        BRIGHT_GREEN,
        BRIGHT_LAVENDER,
        BRIGHT_MAROON,
        BRIGHT_PINK,
        BRIGHT_TURQUOISE,
        BRIGHT_UBE,
        BRILLIANT_LAVENDER,
        BRILLIANT_ROSE,
        BRINK_PINK,
        BRITISH_RACING_GREEN,
        BRONZE,
        BROWN_TRADITIONAL,
        BROWN_WEB,
        BUBBLE_GUM,
        BUBBLES,
        BUFF,
        BULGARIAN_ROSE,
        BURGUNDY,
        BURLYWOOD,
        BURNT_ORANGE,
        BURNT_SIENNA,
        BURNT_UMBER,
        BYZANTINE,
        BYZANTIUM,
        CADET,
        CADET_BLUE,
        CADET_GREY,
        CADMIUM_GREEN,
        CADMIUM_ORANGE,
        CADMIUM_RED,
        CADMIUM_YELLOW,
        CAF_AU_LAIT,
        CAF_NOIR,
        CAL_POLY_GREEN,
        CAMBRIDGE_BLUE,
        CAMEL,
        CAMEO_PINK,
        CAMOUFLAGE_GREEN,
        CANARY_YELLOW,
        CANDY_APPLE_RED,
        CANDY_PINK,
        CAPRI,
        CAPUT_MORTUUM,
        CARDINAL,
        CARIBBEAN_GREEN,
        CARMINE,
        CARMINE_M_P,
        CARMINE_PINK,
        CARMINE_RED,
        CARNATION_PINK,
        CARNELIAN,
        CAROLINA_BLUE,
        CARROT_ORANGE,
        CATALINA_BLUE,
        CEIL,
        CELADON,
        CELADON_BLUE,
        CELADON_GREEN,
        CELESTE_COLOUR,
        CELESTIAL_BLUE,
        CERISE,
        CERISE_PINK,
        CERULEAN,
        CERULEAN_BLUE,
        CERULEAN_FROST,
        CG_BLUE,
        CG_RED,
        CHAMOISEE,
        CHAMPAGNE,
        CHARCOAL,
        CHARM_PINK,
        CHARTREUSE_TRADITIONAL,
        CHARTREUSE_WEB,
        CHERRY,
        CHERRY_BLOSSOM_PINK,
        CHESTNUT,
        CHINA_PINK,
        CHINA_ROSE,
        CHINESE_RED,
        CHOCOLATE_TRADITIONAL,
        CHOCOLATE_WEB,
        CHROME_YELLOW,
        CINEREOUS,
        CINNABAR,
        CINNAMON,
        CITRINE,
        CLASSIC_ROSE,
        COBALT,
        COCOA_BROWN,
        COFFEE,
        COLUMBIA_BLUE,
        CONGO_PINK,
        COOL_BLACK,
        COOL_GREY,
        COPPER,
        COPPER_CRAYOLA,
        COPPER_PENNY,
        COPPER_RED,
        COPPER_ROSE,
        COQUELICOT,
        CORAL,
        CORAL_PINK,
        CORAL_RED,
        CORDOVAN,
        CORN,
        CORNELL_RED,
        CORNFLOWER_BLUE,
        CORNSILK,
        COSMIC_LATTE,
        COTTON_CANDY,
        CREAM,
        CRIMSON,
        CRIMSON_GLORY,
        CYAN,
        CYAN_PROCESS,
        DAFFODIL,
        DANDELION,
        DARK_BLUE,
        DARK_BROWN,
        DARK_BYZANTIUM,
        DARK_CANDY_APPLE_RED,
        DARK_CERULEAN,
        DARK_CHESTNUT,
        DARK_CORAL,
        DARK_CYAN,
        DARK_ELECTRIC_BLUE,
        DARK_GOLDENROD,
        DARK_GRAY,
        DARK_GREEN,
        DARK_IMPERIAL_BLUE,
        DARK_JUNGLE_GREEN,
        DARK_KHAKI,
        DARK_LAVA,
        DARK_LAVENDER,
        DARK_MAGENTA,
        DARK_MIDNIGHT_BLUE,
        DARK_OLIVE_GREEN,
        DARK_ORANGE,
        DARK_ORCHID,
        DARK_PASTEL_BLUE,
        DARK_PASTEL_GREEN,
        DARK_PASTEL_PURPLE,
        DARK_PASTEL_RED,
        DARK_PINK,
        DARK_POWDER_BLUE,
        DARK_RASPBERRY,
        DARK_RED,
        DARK_SALMON,
        DARK_SCARLET,
        DARK_SEA_GREEN,
        DARK_SIENNA,
        DARK_SLATE_BLUE,
        DARK_SLATE_GRAY,
        DARK_SPRING_GREEN,
        DARK_TAN,
        DARK_TANGERINE,
        DARK_TAUPE,
        DARK_TERRA_COTTA,
        DARK_TURQUOISE,
        DARK_VIOLET,
        DARK_YELLOW,
        DARTMOUTH_GREEN,
        DAVY_S_GREY,
        DEBIAN_RED,
        DEEP_CARMINE,
        DEEP_CARMINE_PINK,
        DEEP_CARROT_ORANGE,
        DEEP_CERISE,
        DEEP_CHAMPAGNE,
        DEEP_CHESTNUT,
        DEEP_COFFEE,
        DEEP_FUCHSIA,
        DEEP_JUNGLE_GREEN,
        DEEP_LILAC,
        DEEP_MAGENTA,
        DEEP_PEACH,
        DEEP_PINK,
        DEEP_RUBY,
        DEEP_SAFFRON,
        DEEP_SKY_BLUE,
        DEEP_TUSCAN_RED,
        DENIM,
        DESERT,
        DESERT_SAND,
        DIM_GRAY,
        DODGER_BLUE,
        DOGWOOD_ROSE,
        DOLLAR_BILL,
        DRAB,
        DUKE_BLUE,
        EARTH_YELLOW,
        EBONY,
        ECRU,
        EGGPLANT,
        EGGSHELL,
        EGYPTIAN_BLUE,
        ELECTRIC_BLUE,
        ELECTRIC_CRIMSON,
        ELECTRIC_CYAN,
        ELECTRIC_GREEN,
        ELECTRIC_INDIGO,
        ELECTRIC_LAVENDER,
        ELECTRIC_LIME,
        ELECTRIC_PURPLE,
        ELECTRIC_ULTRAMARINE,
        ELECTRIC_VIOLET,
        ELECTRIC_YELLOW,
        EMERALD,
        ENGLISH_LAVENDER,
        ETON_BLUE,
        FALLOW,
        FALU_RED,
        FANDANGO,
        FASHION_FUCHSIA,
        FAWN,
        FELDGRAU,
        FERN_GREEN,
        FERRARI_RED,
        FIELD_DRAB,
        FIRE_ENGINE_RED,
        FIREBRICK,
        FLAME,
        FLAMINGO_PINK,
        FLAVESCENT,
        FLAX,
        FLORAL_WHITE,
        FLUORESCENT_ORANGE,
        FLUORESCENT_PINK,
        FLUORESCENT_YELLOW,
        FOLLY,
        FOREST_GREEN_TRADITIONAL,
        FOREST_GREEN_WEB,
        FRENCH_BEIGE,
        FRENCH_BLUE,
        FRENCH_LILAC,
        FRENCH_LIME,
        FRENCH_RASPBERRY,
        FRENCH_ROSE,
        FUCHSIA,
        FUCHSIA_CRAYOLA,
        FUCHSIA_PINK,
        FUCHSIA_ROSE,
        FULVOUS,
        FUZZY_WUZZY,
        GAINSBORO,
        GAMBOGE,
        GHOST_WHITE,
        GINGER,
        GLAUCOUS,
        GLITTER,
        GOLD_METALLIC,
        GOLD_WEB_GOLDEN,
        GOLDEN_BROWN,
        GOLDEN_POPPY,
        GOLDEN_YELLOW,
        GOLDENROD,
        GRANNY_SMITH_APPLE,
        GRAY,
        GRAY_ASPARAGUS,
        GRAY_HTML_CSS_GRAY,
        GRAY_X11_GRAY,
        GREEN_COLOR_WHEEL_X11_GREEN,
        GREEN_CRAYOLA,
        GREEN_HTML_CSS_GREEN,
        GREEN_MUNSELL,
        GREEN_NCS,
        GREEN_PIGMENT,
        GREEN_RYB,
        GREEN_YELLOW,
        GRULLO,
        GUPPIE_GREEN,
        HALAY_BE,
        HAN_BLUE,
        HAN_PURPLE,
        HANSA_YELLOW,
        HARLEQUIN,
        HARVARD_CRIMSON,
        HARVEST_GOLD,
        HEART_GOLD,
        HELIOTROPE,
        HOLLYWOOD_CERISE,
        HONEYDEW,
        HONOLULU_BLUE,
        HOOKER_S_GREEN,
        HOT_MAGENTA,
        HOT_PINK,
        HUNTER_GREEN,
        ICEBERG,
        ICTERINE,
        IMPERIAL_BLUE,
        INCHWORM,
        INDIA_GREEN,
        INDIAN_RED,
        INDIAN_YELLOW,
        INDIGO,
        INDIGO_DYE,
        INDIGO_WEB,
        INTERNATIONAL_KLEIN_BLUE,
        INTERNATIONAL_ORANGE_AEROSPACE,
        INTERNATIONAL_ORANGE_ENGINEERING,
        INTERNATIONAL_ORANGE_GOLDEN_GATE_BRIDGE,
        IRIS,
        ISABELLINE,
        ISLAMIC_GREEN,
        IVORY,
        JADE,
        JASMINE,
        JASPER,
        JAZZBERRY_JAM,
        JET,
        JONQUIL,
        JUNE_BUD,
        JUNGLE_GREEN,
        KELLY_GREEN,
        KENYAN_COPPER,
        KHAKI_HTML_CSS_KHAKI,
        KHAKI_X11_LIGHT_KHAKI,
        KU_CRIMSON,
        LA_SALLE_GREEN,
        LANGUID_LAVENDER,
        LAPIS_LAZULI,
        LASER_LEMON,
        LAUREL_GREEN,
        LAVA,
        LAVENDER_BLUE,
        LAVENDER_BLUSH,
        LAVENDER_FLORAL,
        LAVENDER_GRAY,
        LAVENDER_INDIGO,
        LAVENDER_MAGENTA,
        LAVENDER_MIST,
        LAVENDER_PINK,
        LAVENDER_PURPLE,
        LAVENDER_ROSE,
        LAVENDER_WEB,
        LAWN_GREEN,
        LEMON,
        LEMON_CHIFFON,
        LEMON_LIME,
        LICORICE,
        LIGHT_APRICOT,
        LIGHT_BLUE,
        LIGHT_BROWN,
        LIGHT_CARMINE_PINK,
        LIGHT_CORAL,
        LIGHT_CORNFLOWER_BLUE,
        LIGHT_CRIMSON,
        LIGHT_CYAN,
        LIGHT_FUCHSIA_PINK,
        LIGHT_GOLDENROD_YELLOW,
        LIGHT_GRAY,
        LIGHT_GREEN,
        LIGHT_KHAKI,
        LIGHT_PASTEL_PURPLE,
        LIGHT_PINK,
        LIGHT_RED_OCHRE,
        LIGHT_SALMON,
        LIGHT_SALMON_PINK,
        LIGHT_SEA_GREEN,
        LIGHT_SKY_BLUE,
        LIGHT_SLATE_GRAY,
        LIGHT_TAUPE,
        LIGHT_THULIAN_PINK,
        LIGHT_YELLOW,
        LILAC,
        LIME_COLOR_WHEEL,
        LIME_GREEN,
        LIME_WEB_X11_GREEN,
        LIMERICK,
        LINCOLN_GREEN,
        LINEN,
        LION,
        LITTLE_BOY_BLUE,
        LIVER,
        LUST,
        MAGENTA,
        MAGENTA_DYE,
        MAGENTA_PROCESS,
        MAGIC_MINT,
        MAGNOLIA,
        MAHOGANY,
        MAIZE,
        MAJORELLE_BLUE,
        MALACHITE,
        MANATEE,
        MANGO_TANGO,
        MANTIS,
        MARDI_GRAS,
        MAROON_CRAYOLA,
        MAROON_HTML_CSS,
        MAROON_X11,
        MAUVE,
        MAUVE_TAUPE,
        MAUVELOUS,
        MAYA_BLUE,
        MEAT_BROWN,
        MEDIUM_AQUAMARINE,
        MEDIUM_BLUE,
        MEDIUM_CANDY_APPLE_RED,
        MEDIUM_CARMINE,
        MEDIUM_CHAMPAGNE,
        MEDIUM_ELECTRIC_BLUE,
        MEDIUM_JUNGLE_GREEN,
        MEDIUM_LAVENDER_MAGENTA,
        MEDIUM_ORCHID,
        MEDIUM_PERSIAN_BLUE,
        MEDIUM_PURPLE,
        MEDIUM_RED_VIOLET,
        MEDIUM_RUBY,
        MEDIUM_SEA_GREEN,
        MEDIUM_SLATE_BLUE,
        MEDIUM_SPRING_BUD,
        MEDIUM_SPRING_GREEN,
        MEDIUM_TAUPE,
        MEDIUM_TURQUOISE,
        MEDIUM_TUSCAN_RED,
        MEDIUM_VERMILION,
        MEDIUM_VIOLET_RED,
        MELLOW_APRICOT,
        MELLOW_YELLOW,
        MELON,
        MIDNIGHT_BLUE,
        MIDNIGHT_GREEN_EAGLE_GREEN,
        MIKADO_YELLOW,
        MINT,
        MINT_CREAM,
        MINT_GREEN,
        MISTY_ROSE,
        MOCCASIN,
        MODE_BEIGE,
        MOONSTONE_BLUE,
        MORDANT_RED_19,
        MOSS_GREEN,
        MOUNTAIN_MEADOW,
        MOUNTBATTEN_PINK,
        MSU_GREEN,
        MULBERRY,
        MUSTARD,
        MYRTLE,
        NADESHIKO_PINK,
        NAPIER_GREEN,
        NAPLES_YELLOW,
        NAVAJO_WHITE,
        NAVY_BLUE,
        NEON_CARROT,
        NEON_FUCHSIA,
        NEON_GREEN,
        NEW_YORK_PINK,
        NON_PHOTO_BLUE,
        NORTH_TEXAS_GREEN,
        OCEAN_BOAT_BLUE,
        OCHRE,
        OFFICE_GREEN,
        OLD_GOLD,
        OLD_LACE,
        OLD_LAVENDER,
        OLD_MAUVE,
        OLD_ROSE,
        OLIVE,
        OLIVE_DRAB_7,
        OLIVE_DRAB_WEB_OLIVE_DRAB_3,
        OLIVINE,
        ONYX,
        OPERA_MAUVE,
        ORANGE_COLOR_WHEEL,
        ORANGE_PEEL,
        ORANGE_RED,
        ORANGE_RYB,
        ORANGE_WEB_COLOR,
        ORCHID,
        OTTER_BROWN,
        OU_CRIMSON_RED,
        OUTER_SPACE,
        OUTRAGEOUS_ORANGE,
        OXFORD_BLUE,
        PAKISTAN_GREEN,
        PALATINATE_BLUE,
        PALATINATE_PURPLE,
        PALE_AQUA,
        PALE_BLUE,
        PALE_BROWN,
        PALE_CARMINE,
        PALE_CERULEAN,
        PALE_CHESTNUT,
        PALE_COPPER,
        PALE_CORNFLOWER_BLUE,
        PALE_GOLD,
        PALE_GOLDENROD,
        PALE_GREEN,
        PALE_LAVENDER,
        PALE_MAGENTA,
        PALE_PINK,
        PALE_PLUM,
        PALE_RED_VIOLET,
        PALE_ROBIN_EGG_BLUE,
        PALE_SILVER,
        PALE_SPRING_BUD,
        PALE_TAUPE,
        PALE_VIOLET_RED,
        PANSY_PURPLE,
        PAPAYA_WHIP,
        PARIS_GREEN,
        PASTEL_BLUE,
        PASTEL_BROWN,
        PASTEL_GRAY,
        PASTEL_GREEN,
        PASTEL_MAGENTA,
        PASTEL_ORANGE,
        PASTEL_PINK,
        PASTEL_PURPLE,
        PASTEL_RED,
        PASTEL_VIOLET,
        PASTEL_YELLOW,
        PATRIARCH,
        PAYNE_S_GREY,
        PEACH,
        PEACH_CRAYOLA,
        PEACH_ORANGE,
        PEACH_PUFF,
        PEACH_YELLOW,
        PEAR,
        PEARL,
        PEARL_AQUA,
        PEARLY_PURPLE,
        PERIDOT,
        PERIWINKLE,
        PERSIAN_BLUE,
        PERSIAN_GREEN,
        PERSIAN_INDIGO,
        PERSIAN_ORANGE,
        PERSIAN_PINK,
        PERSIAN_PLUM,
        PERSIAN_RED,
        PERSIAN_ROSE,
        PERSIMMON,
        PERU,
        PHLOX,
        PHTHALO_BLUE,
        PHTHALO_GREEN,
        PIGGY_PINK,
        PINE_GREEN,
        PINK,
        PINK_LACE,
        PINK_ORANGE,
        PINK_PEARL,
        PINK_SHERBET,
        PISTACHIO,
        PLATINUM,
        PLUM_TRADITIONAL,
        PLUM_WEB,
        PORTLAND_ORANGE,
        POWDER_BLUE_WEB,
        PRINCETON_ORANGE,
        PRUNE,
        PRUSSIAN_BLUE,
        PSYCHEDELIC_PURPLE,
        PUCE,
        PUMPKIN,
        PURPLE_HEART,
        PURPLE_HTML_CSS,
        PURPLE_MOUNTAIN_MAJESTY,
        PURPLE_MUNSELL,
        PURPLE_PIZZAZZ,
        PURPLE_TAUPE,
        PURPLE_X11,
        QUARTZ,
        RACKLEY,
        RADICAL_RED,
        RAJAH,
        RASPBERRY,
        RASPBERRY_GLACE,
        RASPBERRY_PINK,
        RASPBERRY_ROSE,
        RAW_UMBER,
        RAZZLE_DAZZLE_ROSE,
        RAZZMATAZZ,
        RED,
        RED_BROWN,
        RED_DEVIL,
        RED_MUNSELL,
        RED_NCS,
        RED_ORANGE,
        RED_PIGMENT,
        RED_RYB,
        RED_VIOLET,
        REDWOOD,
        REGALIA,
        RESOLUTION_BLUE,
        RICH_BLACK,
        RICH_BRILLIANT_LAVENDER,
        RICH_CARMINE,
        RICH_ELECTRIC_BLUE,
        RICH_LAVENDER,
        RICH_LILAC,
        RICH_MAROON,
        RIFLE_GREEN,
        ROBIN_EGG_BLUE,
        ROSE,
        ROSE_BONBON,
        ROSE_EBONY,
        ROSE_GOLD,
        ROSE_MADDER,
        ROSE_PINK,
        ROSE_QUARTZ,
        ROSE_TAUPE,
        ROSE_VALE,
        ROSEWOOD,
        ROSSO_CORSA,
        ROSY_BROWN,
        ROYAL_AZURE,
        ROYAL_BLUE_TRADITIONAL,
        ROYAL_BLUE_WEB,
        ROYAL_FUCHSIA,
        ROYAL_PURPLE,
        ROYAL_YELLOW,
        RUBINE_RED,
        RUBY,
        RUBY_RED,
        RUDDY,
        RUDDY_BROWN,
        RUDDY_PINK,
        RUFOUS,
        RUSSET,
        RUST,
        RUSTY_RED,
        SACRAMENTO_STATE_GREEN,
        SADDLE_BROWN,
        SAFETY_ORANGE_BLAZE_ORANGE,
        SAFFRON,
        SALMON,
        SALMON_PINK,
        SAND,
        SAND_DUNE,
        SANDSTORM,
        SANDY_BROWN,
        SANDY_TAUPE,
        SANGRIA,
        SAP_GREEN,
        SAPPHIRE,
        SAPPHIRE_BLUE,
        SATIN_SHEEN_GOLD,
        SCARLET,
        SCARLET_CRAYOLA,
        SCHOOL_BUS_YELLOW,
        SCREAMIN_GREEN,
        SEA_BLUE,
        SEA_GREEN,
        SEAL_BROWN,
        SEASHELL,
        SELECTIVE_YELLOW,
        SEPIA,
        SHADOW,
        SHAMROCK_GREEN,
        SHOCKING_PINK,
        SHOCKING_PINK_CRAYOLA,
        SIENNA,
        SILVER,
        SINOPIA,
        SKOBELOFF,
        SKY_BLUE,
        SKY_MAGENTA,
        SLATE_BLUE,
        SLATE_GRAY,
        SMALT_DARK_POWDER_BLUE,
        SMOKEY_TOPAZ,
        SMOKY_BLACK,
        SNOW,
        SPIRO_DISCO_BALL,
        SPRING_BUD,
        SPRING_GREEN,
        ST_PATRICK_S_BLUE,
        STEEL_BLUE,
        STIL_DE_GRAIN_YELLOW,
        STIZZA,
        STORMCLOUD,
        STRAW,
        SUNGLOW,
        SUNSET,
        TAN,
        TANGELO,
        TANGERINE,
        TANGERINE_YELLOW,
        TANGO_PINK,
        TAUPE,
        TAUPE_GRAY,
        TEA_GREEN,
        TEA_ROSE_ORANGE,
        TEA_ROSE_ROSE,
        TEAL,
        TEAL_BLUE,
        TEAL_GREEN,
        TELEMAGENTA,
        TENN_TAWNY,
        TERRA_COTTA,
        THISTLE,
        THULIAN_PINK,
        TICKLE_ME_PINK,
        TIFFANY_BLUE,
        TIGER_S_EYE,
        TIMBERWOLF,
        TITANIUM_YELLOW,
        TOMATO,
        TOOLBOX,
        TOPAZ,
        TRACTOR_RED,
        TROLLEY_GREY,
        TROPICAL_RAIN_FOREST,
        TRUE_BLUE,
        TUFTS_BLUE,
        TUMBLEWEED,
        TURKISH_ROSE,
        TURQUOISE,
        TURQUOISE_BLUE,
        TURQUOISE_GREEN,
        TUSCAN_RED,
        TWILIGHT_LAVENDER,
        TYRIAN_PURPLE,
        UA_BLUE,
        UA_RED,
        UBE,
        UCLA_BLUE,
        UCLA_GOLD,
        UFO_GREEN,
        ULTRA_PINK,
        ULTRAMARINE,
        ULTRAMARINE_BLUE,
        UMBER,
        UNBLEACHED_SILK,
        UNITED_NATIONS_BLUE,
        UNIVERSITY_OF_CALIFORNIA_GOLD,
        UNMELLOW_YELLOW,
        UP_FOREST_GREEN,
        UP_MAROON,
        UPSDELL_RED,
        UROBILIN,
        USAFA_BLUE,
        USC_CARDINAL,
        USC_GOLD,
        UTAH_CRIMSON,
        VANILLA,
        VEGAS_GOLD,
        VENETIAN_RED,
        VERDIGRIS,
        VERMILION_CINNABAR,
        VERMILION_PLOCHERE,
        VERONICA,
        VIOLET,
        VIOLET_BLUE,
        VIOLET_COLOR_WHEEL,
        VIOLET_RYB,
        VIOLET_WEB,
        VIRIDIAN,
        VIVID_AUBURN,
        VIVID_BURGUNDY,
        VIVID_CERISE,
        VIVID_TANGERINE,
        VIVID_VIOLET,
        WARM_BLACK,
        WATERSPOUT,
        WENGE,
        WHEAT,
        WHITE,
        WHITE_SMOKE,
        WILD_BLUE_YONDER,
        WILD_STRAWBERRY,
        WILD_WATERMELON,
        WINE,
        WINE_DREGS,
        WISTERIA,
        WOOD_BROWN,
        XANADU,
        YALE_BLUE,
        YELLOW,
        YELLOW_GREEN,
        YELLOW_MUNSELL,
        YELLOW_NCS,
        YELLOW_ORANGE,
        YELLOW_PROCESS,
        YELLOW_RYB,
        ZAFFRE,
        ZINNWALDITE_BROWN
    };

    static glm::vec3 color(const Color &color);
public:
    static const char *string_format(const char *fmt, ...) {
        static char sBuffer[4096] = "";

        va_list args;
        va_start(args, fmt);
        vsnprintf(sBuffer, 2048, fmt, args);
        //    perror (sBuffer);
        va_end(args);
        return sBuffer;
    }


    //    static std::string to_string(const glm::vec2 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }
    //
    //    static std::string to_string(const glm::vec3 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }
    //
    //    static std::string to_string(const glm::vec4 &from) {
    //        std::string ret(string_format(
    //        FORMATSTRING_MAT4x4, m_buffer[0], m_buffer[1], m_buffer[2],
    //        m_buffer[3], m_buffer[4], m_buffer[5], m_buffer[6], m_buffer[7],
    //        m_buffer[8], m_buffer[9], m_buffer[10], m_buffer[11],
    //        m_buffer[12], m_buffer[13],
    //                                      m_buffer[14], m_buffer[15]));
    //        return ret;
    //    }

    //    glm::mat4 m;
    //    const btMatrix3x3 &basis = m_btTransform->getBasis();
    //    for (int r = 0; r < 3; r++)
    //    {
    //        for (int c = 0; c < 3; c++)
    //        {
    //            m[c][r] = basis[r][c];
    //        }
    //    }
    //
    //    btVector3 origin = m_btTransform->getOrigin();
    //
    //    m[3][0] = origin.getX();
    //    m[3][1] = origin.getY();
    //    m[3][2] = origin.getZ();
    //    // unit scale
    //    m[0][3] = 0.0f;
    //    m[1][3] = 0.0f;
    //    m[2][3] = 0.0f;
    //    m[3][3] = 1.0f;
    //
    //    return m;
    static std::string to_string(const glm::mat4x4 &from) {

        std::string ret(string_format(
                FORMATSTRING_MAT4x4, from[0][0], from[0][1], from[0][2], from[0][3],
                from[1][0], from[1][1], from[1][2], from[1][3], from[2][0],
                from[2][1], from[2][2], from[2][3], from[3][0], from[3][1],
                from[3][2], from[3][3]));
        return ret;
    }

    static std::string to_string(const float *transformMatrix) {

        if (transformMatrix) {

            std::string ret(string_format(
                    FORMATSTRING_MAT4x4, transformMatrix[0], transformMatrix[1],
                    transformMatrix[2], transformMatrix[3], transformMatrix[4],
                    transformMatrix[5], transformMatrix[6], transformMatrix[7],
                    transformMatrix[8], transformMatrix[9], transformMatrix[10],
                    transformMatrix[11], transformMatrix[12], transformMatrix[13],
                    transformMatrix[14], transformMatrix[15]));
            return ret;
        }
        return "NULL";
    }

    static bool validUrl(const std::string &url) {
        std::regex url_regex(
                R"(^(([^:\/?#]+):)?(//([^\/?#]*))?([^?#]*)(\?([^#]*))?(#(.*))?)",
                std::regex::extended);
        std::smatch url_match_result;

        bool ret = std::regex_match(url, url_match_result, url_regex);
        assert(ret);
        return ret;
    }

    static uint64_t timeSinceEpochMillisec() {
        using namespace std::chrono;
        return duration_cast<milliseconds>(
                system_clock::now().time_since_epoch())
                .count();
    }

    static std::string tolower(std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                       [](unsigned char c) { return std::tolower(c); });
        return str;
    }

    static char *loadFile(const std::string &filePath, size_t &fileSize) {
        const std::string base_path(SDL_GetBasePath());

        std::string jsonFilePath = base_path + filePath;
        char *_buffer = nullptr;

        SDL_RWops *rw = SDL_RWFromFile(jsonFilePath.c_str(), "rb");
        if (rw) {
            fileSize = SDL_RWsize(rw);

            _buffer = (char *)malloc(fileSize + 1);
            memset(_buffer, 0, sizeof(char) * fileSize + 1);

            Sint64 nb_read_total = 0, nb_read = 1;
            char *buf = (char *)_buffer;
            while (nb_read_total < fileSize && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (fileSize - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
            }
            SDL_RWclose(rw);
            if (nb_read_total != fileSize) {
                free(_buffer);
                _buffer = nullptr;
            }
        }
        return _buffer;
    }

    static char *loadFile(const std::string &filePath) {
        size_t throwaway;
        return loadFile(filePath, throwaway);
    }

    static unsigned int getClosestValidGLDim(const unsigned int dim) {
        for (unsigned int shift = 0; shift < 12; shift++) {
            if ((1 << shift) > dim)
                return 1 << (shift);
        }
        return 1 << 11;
    }

    static void *loadImage(const std::string &filePath, int *width, int *height,
                           int *channels_in_file);

    static bool compileShader(GLuint &shader, GLenum type,
                              const std::string &source) {
        GLint status(GL_TRUE);
        const GLchar *_source = (GLchar *)source.c_str();

        if (!_source) {
            SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                         "Failed to load vertex shader");
            return false;
        }

        shader = glCreateShader(type);
        glShaderSource(shader, 1, &_source, NULL);
        Util::glErrorCheck();
        glCompileShader(shader);
        Util::glErrorCheck();

        glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
        Util::glErrorCheck();
        if (status == GL_FALSE) {

            GLint logLength;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
            Util::glErrorCheck();
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetShaderInfoLog(shader, logLength, &logLength, log);
                Util::glErrorCheck();
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Shader compile log:\n%s", log);
                free(log);
            }
            glDeleteShader(shader);

            return false;
        }

        return true;
    }

    static bool linkProgram(GLuint programPointer) {
        GLint status(GL_FALSE);

        glLinkProgram(programPointer);

        glGetProgramiv(programPointer, GL_LINK_STATUS, &status);
        if (status == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(programPointer, GL_INFO_LOG_LENGTH, &logLength);
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramInfoLog(programPointer, logLength, &logLength, log);
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Program link log:\n%s", log);
                free(log);
            }

            return false;
        }

        return true;
    }

    static bool validateProgram(GLuint programPointer) {
        GLint status(GL_FALSE);

        glValidateProgram(programPointer);
        Util::glErrorCheck();

        glGetProgramiv(programPointer, GL_VALIDATE_STATUS, &status);
        Util::glErrorCheck();
        if (status == GL_FALSE) {
            GLint logLength;
            glGetProgramiv(programPointer, GL_INFO_LOG_LENGTH, &logLength);
            Util::glErrorCheck();
            if (logLength > 0) {
                GLchar *log = (GLchar *)malloc(logLength);
                glGetProgramInfoLog(programPointer, logLength, &logLength, log);
                Util::glErrorCheck();
                SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                             "Program validate log:\n%s", log);
                free(log);
            }
            return false;
        }

        return true;
    }

    static void printGLInfo() {
        // gl begin printGLInfo
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VERSION",
                       (const char *)glGetString(GL_VERSION));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_VENDOR",
                       (const char *)glGetString(GL_VENDOR));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n", "GL_RENDERER",
                       (const char *)glGetString(GL_RENDERER));

        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s\n", "GL_EXTENSIONS");
        const char *the_extensions = (const char *)glGetString(GL_EXTENSIONS);
        char *extensions = new char[strlen(the_extensions) + 1];
        SDL_assert(extensions);
        strcpy(extensions, the_extensions);
        char *extension = strtok(extensions, " ");
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
        while (NULL != (extension = strtok(NULL, " "))) {
            SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "\t%s\n", extension);
        }
        delete[] extensions;
        extensions = NULL;

        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s", "GL_EXTENSIONS",
        //    (const char *) glGetString(GL_EXTENSIONS));
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %s\n",
                       "GL_SHADING_LANGUAGE_VERSION",
                       (const char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

        int param;

        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &param);
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                       "The max texture size", param);

        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in vertex shader",
                param);

        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in fragmet shader",
                param);

        glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &param);
        SDL_LogVerbose(
                SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                "The count texture units of allowed for usage in both shaders",
                param);

        //    glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of uniform vectors in the vertex shader", param);
        //
        //    glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of uniform vectors in the fragment shader", param);
        //
        //    glGetIntegerv(GL_MAX_VARYING_VECTORS, &param);
        //    SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n", "The maximumum
        //    amount of varying vectors", param);

        glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &param);
        SDL_LogVerbose(SDL_LOG_CATEGORY_TEST, "%s = %d\n",
                       "The maximumum amount of vertex attributes", param);

        //

        //    GL_MAX_VERTEX_UNIFORM_VECTORS
        //    GL_MAX_FRAGMENT_UNIFORM_VECTORS
        /*
         Actually there is GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, and
         GL_MAX_TEXTURE_IMAGE_UNITS and GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS
         enums. First is for count texture units of allowed for usage in vertex
         shader, second one is for fragment shader, and third is combined for
         both shaders combined.
         */

        // gl end printGLInfo
    }

    static unsigned int getNextPower2(const unsigned int dim,
                                      const unsigned short maxShifts = 12) {
        for (unsigned int shift = 0; shift < maxShifts; shift++) {
            if ((1 << shift) > dim)
                return 1 << (shift);
        }
        return 1 << 11;
    }

    static void *loadDefaultCardImage(int *width, int *height,
                                      int *channels_in_file, size_t *fileSize);

    static void glErrorCheck() {
        do {
            for (int error = glGetError(); error; error = glGetError()) {

                switch (error) {
                    case GL_NO_ERROR:
                        SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
                                    "GL_NO_ERROR - No error has been recorded. The "
                                    "value of this symbolic constant is guaranteed "
                                    "to be 0.");
                        break;
                    case GL_INVALID_ENUM:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_ENUM - An unacceptable value is "
                                "specified for an enumerated argument. The "
                                "offending command is ignored and has no other "
                                "side effect than to set the error flag.");
                        break;
                    case GL_INVALID_VALUE:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_VALUE - A numeric argument is out of "
                                "range. The offending command is ignored and has "
                                "no other side effect than to set the error "
                                "flag.");
                        break;
                    case GL_INVALID_OPERATION:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_OPERATION - The specified operation "
                                "is not allowed in the current state. The "
                                "offending command is ignored and has no other "
                                "side effect than to set the error flag.");
                        break;
                    case GL_INVALID_FRAMEBUFFER_OPERATION:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_INVALID_FRAMEBUFFER_OPERATION - The command "
                                "is trying to render to or read from the "
                                "framebuffer while the currently bound "
                                "framebuffer is not framebuffer complete (i.e. "
                                "the return value from glCheckFramebufferStatus "
                                "is not GL_FRAMEBUFFER_COMPLETE). The offending "
                                "command is ignored and has no other side effect "
                                "than to set the error flag.");
                        break;
                    case GL_OUT_OF_MEMORY:
                        SDL_LogError(
                                SDL_LOG_CATEGORY_APPLICATION,
                                "GL_OUT_OF_MEMORY - There is not enough memory "
                                "left to execute the command. The state of the GL "
                                "is undefined, except for the state of the error "
                                "flags, after this error is recorded.");
                        break;
                    default:
                        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Unknown (%x)",
                                     error);
                }
            }
        } while (0);
    }
};

#endif /* Util_h */
