Generate a keypair
```
openssl req -nodes -x509 -sha256 -newkey rsa:4096 -keyout "private.key" -out "public.crt" -days 365 
#-subj "/C=NL/ST=Zuid Holland/L=Rotterdam/O=Sparkling Network/OU=IT Dept/CN=$(whoami)s Sign Key"
```

Sign the file
```
openssl dgst -sha256 -sign "private.key" -out data.txt.sha256 data.txt
```

Verifiy the signature
```
openssl dgst -sha256 -verify  <(openssl x509 -in "public.crt"  -pubkey -noout) -signature data.txt.sha256 data.txt
```
Source: https://raymii.org/s/tutorials/Sign_and_verify_text_files_to_public_keys_via_the_OpenSSL_Command_Line.html
