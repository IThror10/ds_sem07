import pickle
import rsa

BLOCK_SIZE_BITS = 512
KEYS_FILE = "keys.dump"

class KeysGenerator():
    def generate():
        with open(KEYS_FILE, "wb") as dst:
            (ok, sk) = rsa.newkeys(BLOCK_SIZE_BITS, True)
            pickle.dump(ok, dst)
            pickle.dump(sk, dst)

    def read():
        try:
            with open(KEYS_FILE, "rb") as src:
                return pickle.load(src), pickle.load(src)
        except:
            raise RuntimeError("Launch <<keys.py>> file to Generate Keys")


if __name__ == "__main__":
    KeysGenerator.generate()