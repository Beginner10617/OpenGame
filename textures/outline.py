from PIL import Image, ImageDraw

# UV coordinates (u,v) in range [0,1]
uvs = [
    (0.005, 0.000),
    (0.018, 0.527),
    (0.308, 0.659),
    (0.459, 1.000),
    (0.712, 1.000),
    (0.871, 0.718),
    (0.988, 0.670),
    (1.000, 0.000)
]

# Load PNG
img = Image.open("car-side.png").convert("RGBA")

w, h = img.size

# Convert UV -> pixel coordinates
# (v is flipped because image y grows downward)
pts = [
    (u * w, (1.0 - v) * h)
    for (u, v) in uvs
]

draw = ImageDraw.Draw(img)

# Draw closed loop
draw.line(
    pts + [pts[0]],   # append first point to close loop
    fill=(0, 0, 0, 255),
    width=3
)

# Save result
img.save("output.png")
