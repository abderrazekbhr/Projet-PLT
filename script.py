import os
import subprocess

# Create the 'results' directory if it doesn't exist
os.makedirs("results", exist_ok=True)

try:
    # Find all files with .mak extension
    makefiles = subprocess.check_output(["find", ".", "-type", "f", "-name", "*.mak"], text=True)
    makefiles = makefiles.strip().split("\n")
    makefiles="grad.mak"
    #      gv1D.mak  gv2D.mak  seuil.mak  sobel.mak
    if makefile and not makefile.startswith("./sobel"):
        # Run the make command for each .mak file
        make_command = f"make -f {makefile}"
        try:
            subprocess.run(make_command, shell=True, check=True)
        except subprocess.CalledProcessError as e:
            print(f"Error executing make command '{make_command}': {e}")
        
        # Ensure the '../images' directory exists
        images_dir = "../images"
        if not os.path.isdir(images_dir):
            print(f"Images directory '{images_dir}' does not exist. Skipping.")
        
        images = os.listdir(images_dir)
        filename = os.path.splitext(os.path.basename(makefile))[0]  # Remove directory and extension

        # Process each image
        for img in images:
            img_path = os.path.join(images_dir, img)

            if os.path.isfile(img_path) and img.endswith(".gdr"):  # Only process .gdr files
                imgname = os.path.splitext(img)[0]  # Remove extension
                output_path = os.path.join("results", f"{imgname}_{filename}.jpg")
                # Run the processing command

                if filename == "seuil":
                    process_command = f"./{filename}.x '{img_path}' '{output_path}' 120"
                else:
                    process_command = f"./{filename}.x '{img_path}' '{output_path}'"
                try:
                    subprocess.run(process_command, shell=True, check=True)
                except subprocess.CalledProcessError as e:
                    print(f"Error processing image '{img_path}' with command '{process_command}': {e}")

except subprocess.CalledProcessError as e:
    print(f"Error finding .mak files: {e}")
except Exception as e:
    print(f"An unexpected error occurred: {e}")
    