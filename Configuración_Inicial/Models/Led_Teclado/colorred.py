#

from PIL import Image
import numpy as np

# Cargar la imagen que se ha subido
input_image_path = "LED_Keyboard_BaseColor.png"   # Reemplaza con la ruta a tu imagen
image = Image.open(input_image_path)

# Convertir la imagen a un array de numpy para manipular los colores
image_array = np.array(image)

# Definir los colores RGB para el gradiente
blue = np.array([71, 234, 239])   # Azul clarito
pink = np.array([255, 108, 255])   # Rosa
red = np.array([241, 232, 83])        # Rojo
yellow = np.array([236, 28, 36])   # Amarillo

# Crear un gradiente entre los colores definidos (azul clarito -> rosa -> rojo -> amarillo)
gradients = np.vstack([
    np.linspace(blue, pink, num=256),   # Gradiente de azul a rosa
    np.linspace(pink, red, num=256),    # Gradiente de rosa a rojo
    np.linspace(red, yellow, num=256)   # Gradiente de rojo a amarillo
])

# Umbral para detectar los tonos cercanos al blanco (píxeles que sean muy claros)
light_threshold = 220  # Umbral para detectar píxeles similares al blanco

# Cambiar los píxeles cercanos al blanco (tonos claros) a colores RGB
for i in range(image_array.shape[0]):
    for j in range(image_array.shape[1]):
        # Si el píxel es cercano al blanco, cambiar su color
        if np.all(image_array[i, j] >= [light_threshold, light_threshold, light_threshold]):
            gradient_index = int((i / image_array.shape[0]) * gradients.shape[0])  # índice basado en la posición de la fila
            image_array[i, j] = gradients[gradient_index]  # Asignar el color del gradiente

# Convertir de nuevo el array a imagen
modified_image = Image.fromarray(image_array)

# Guardar la imagen modificada
modified_image.save("imagen_modificada_rgb_gradiente_tonos_claros.png")

# Mostrar la nueva imagen con el efecto RGB aplicado a tonos claros
modified_image.show()
