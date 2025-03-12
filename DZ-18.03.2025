abstract class Color {
    abstract fun toRGB() : RGB
        abstract fun toCMYK() : CMYK
        abstract fun toHSV() : HSV
        abstract fun printInfo()
}

class RGB(var red : Int, var green : Int, var blue : Int) : Color() {

    override fun toRGB() : RGB{
        return this
    }

        override fun toCMYK() : CMYK{
            val r = red / 255.0
            val g = green / 255.0
            val b = blue / 255.0

            val k = 1 - maxOf(r, g, b)
            val c = (1 - r - k) / (1 - k)
            val m = (1 - g - k) / (1 - k)
            val y = (1 - b - k) / (1 - k)

            return CMYK((c * 100).toInt(), (m * 100).toInt(), (y * 100).toInt(), (k * 100).toInt())
    }

        override fun toHSV() : HSV{
            val r = red / 255.0
            val g = green / 255.0
            val b = blue / 255.0

            val max = maxOf(r, g, b)
            val min = minOf(r, g, b)
            val delta = max - min

            val h = when {
                delta == 0.0 -> 0.0
                max == r -> 60 * (((g - b) / delta) % 6)
                max == g -> 60 * (((b - r) / delta) + 2)
                else -> 60 * (((r - g) / delta) + 4)
            }

            val s = if (max == 0.0) 0.0 else delta / max
            val v = max

            return HSV(h.toInt(), (s * 100).toInt(), (v * 100).toInt())
    }

        override fun printInfo() {
        println("RGB: ($red, $green, $blue)")
    }

    fun mix(other: RGB) : RGB{
        return RGB(
            (red + other.red) / 2,
            (green + other.green) / 2,
            (blue + other.blue) / 2
        )
    }
}

class CMYK(var cyan : Int, var magenta : Int, var yellow : Int, var key : Int) : Color() {

    override fun toRGB() : RGB{
        val r = 255 * (1 - cyan / 100.0) * (1 - key / 100.0)
        val g = 255 * (1 - magenta / 100.0) * (1 - key / 100.0)
        val b = 255 * (1 - yellow / 100.0) * (1 - key / 100.0)

        return RGB(r.toInt(), g.toInt(), b.toInt())
    }

        override fun toCMYK() : CMYK{
            return this
    }

        override fun toHSV() : HSV{
            return this.toRGB().toHSV()
    }

        override fun printInfo() {
        println("CMYK: ($cyan%, $magenta%, $yellow%, $key%)")
    }

    fun mix(other: CMYK) : CMYK{
        return CMYK(
            (cyan + other.cyan) / 2,
            (magenta + other.magenta) / 2,
            (yellow + other.yellow) / 2,
            (key + other.key) / 2
        )
    }
}

class HSV(var hue : Int, var saturation : Int, var value : Int) : Color() {

    override fun toRGB() : RGB{
        val h = hue / 60.0
        val s = saturation / 100.0
        val v = value / 100.0

        val c = v * s
        val x = c * (1 - Math.abs((h % 2) - 1))
        val m = v - c

        val(r, g, b) = when {
            h < 1->Triple(c, x, 0.0)
            h < 2->Triple(x, c, 0.0)
            h < 3->Triple(0.0, c, x)
            h < 4->Triple(0.0, x, c)
            h < 5->Triple(x, 0.0, c)
            else->Triple(c, 0.0, x)
        }

        return RGB(
            ((r + m) * 255).toInt(),
            ((g + m) * 255).toInt(),
            ((b + m) * 255).toInt()
        )
    }

        override fun toCMYK() : CMYK{
            return this.toRGB().toCMYK()
    }

        override fun toHSV() : HSV{
            return this
    }

        override fun printInfo() {
        println("HSV: ($hue°, $saturation%, $value%)")
    }

    fun mix(other: HSV) : HSV{
        return HSV(
            (hue + other.hue) / 2,
            (saturation + other.saturation) / 2,
            (value + other.value) / 2
        )
    }
}

fun main() {
    val rgb = RGB(255, 0, 0)
        val cmyk = rgb.toCMYK()
        val hsv = rgb.toHSV()

        println("Исходный цвет:")
        rgb.printInfo()
        println("Преобразованный в CMYK:")
        cmyk.printInfo()
        println("Преобразованный в HSV:")
        hsv.printInfo()

        val mixedRGB = rgb.mix(RGB(0, 255, 0)) 
        println("Смешанный цвет (RGB):")
        mixedRGB.printInfo()

        val mixedCMYK = cmyk.mix(CMYK(0, 100, 100, 0))
        println("Смешанный цвет (CMYK):")
        mixedCMYK.printInfo()

        val mixedHSV = hsv.mix(HSV(120, 100, 100)) 
        println("Смешанный цвет (HSV):")
        mixedHSV.printInfo()
}
