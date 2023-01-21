import sys
from certificate import Certificate

class Main():
    def sign(document:str, es_dst:str) -> None:
        text: bytes = Main.__bin_read_file__(document)
        hashed:bytes = Certificate.create_hash(text)
        result:bytes = Certificate.cipher(hashed, Certificate.get_open_key())

        with open(es_dst, "wb") as dst:
            dst.write(result)
        print("Document <<" + document + ">> successfully signed")

    def verify(document, es_src):
        text: bytes = Main.__bin_read_file__(document)
        signed: bytes = Main.__bin_read_file__(es_src)

        if Certificate.verify_sign(text, signed):
            print("Document is verified")
        else:
            print("<<<ERROR>>> Document is NOT verified!")

    def main(argv: list[str]) -> None:
        if len(argv) < 2:
            raise RuntimeError("Wrong args amount:\n\t<Command> <File> [<ES>]")
        elif argv[1].lower() == "sign":
            if len(argv) != 4:
                raise RuntimeError("Wrong args amount for command <Sign>:\n\t Sign <Document> <ES-dst>")
            Main.sign(argv[2], argv[3])
        elif argv[1].lower() == "verify":
            if len(argv) != 4:
                raise RuntimeError("Wrong args amount for command <Check>:\n\t Sign <Document> <ES-src>")
            Main.verify(argv[2], argv[3])
        else:
            raise RuntimeError("Unknown <Command>:\n\t<Command> = {Sign, Verify\}")

    def __bin_read_file__(document: str) -> bytes:
        text: bytes = None
        with open(document, "rb") as src:
            text = src.read()
        return text


if __name__ == "__main__":
    try:
        Main.main(sys.argv)
    except RuntimeError as error:
        print()
        print(error)