import hashlib
import rsa

from keys import KeysGenerator

class Certificate():
    __open_key__, __secret_key__ = KeysGenerator.read()

    def get_open_key():
        return Certificate.__open_key__
    
    def create_hash(text: bytes) -> bytes:
        sha = hashlib.sha256(text)
        return sha.digest()

    def cipher(text: bytes, key: int) -> bytes:
        ciphered = rsa.encrypt(text, key)
        return ciphered

    def verify_sign(text: bytes, es: bytes) -> bool:
        hashed: bytes = Certificate.create_hash(text)
        decoded: bytes = rsa.decrypt(es, Certificate.__secret_key__)
        return decoded == hashed