import sys
from opentdf import TDFClient, NanoTDFClient, OIDCCredentials, LogLevel, TDFStorageType

# encrypt the file and apply the policy on tdf file and also decrypt.
OIDC_ENDPONT = "http://localhost:65432/"
KAS_URL = "http://localhost:65432/api/kas"

try:
    # Create OIDC credentials object
    oidc_creds = OIDCCredentials()

    oidc_creds.set_client_credentials_client_secret(client_id = "tdf-client",
                                 client_secret = "123-456",
                                 organization_name = "tdf",
                                 oidc_endpoint = OIDC_ENDPONT)

    client = TDFClient(oidc_credentials = oidc_creds,
                        kas_url = KAS_URL)
    client.enable_console_logging(LogLevel.Warn)
    #################################################
    # TDF - File API
    ################################################

    client.add_data_attribute("https://example.com/attr/Classification/value/S", KAS_URL)
    #attr = client.subject_attributes()
    #print(f'Attributes are:{attr}')

    sampleTxtStorage = TDFStorageType()
    sampleTxtStorage.set_tdf_storage_file_type("sample.txt")
    client.encrypt_file(sampleTxtStorage, "sample.txt.tdf")

    sampleTdfStorage = TDFStorageType()
    sampleTdfStorage.set_tdf_storage_file_type("sample.txt.tdf")
    client.decrypt_file(sampleTdfStorage, "sample_out.txt")

    #################################################
    # TDF - Data API
    #################################################

    plain_text = 'Hello world!!'
    sampleStringStorage = TDFStorageType()
    sampleStringStorage.set_tdf_storage_string_type(plain_text)
    tdf_data = client.encrypt_data(sampleStringStorage)

    sampleEncryptedStringStorage = TDFStorageType()
    sampleEncryptedStringStorage.set_tdf_storage_string_type(tdf_data)
    decrypted_plain_text = client.decrypt_data(sampleEncryptedStringStorage)

    if plain_text == decrypted_plain_text:
        print("TDF Encrypt/Decrypt is successful!!")
    else:
        print("Error: TDF Encrypt/Decrypt failed!!")


    #################################################
    # Nano TDF - File API
    ################################################

    # create a nano tdf client.
    nano_tdf_client = NanoTDFClient(oidc_credentials = oidc_creds,
                                 kas_url = KAS_URL)
    nano_tdf_client.enable_console_logging(LogLevel.Warn)

    sampleTxtStorageNano = TDFStorageType()
    sampleTxtStorageNano.set_tdf_storage_file_type("sample.txt")
    nano_tdf_client.encrypt_file(sampleTxtStorageNano, "sample.txt.ntdf")

    sampleTdfStorageNano = TDFStorageType()
    sampleTdfStorageNano.set_tdf_storage_file_type("sample.txt.ntdf")
    nano_tdf_client.decrypt_file(sampleTdfStorageNano, "sample_out.nano.txt")

    #################################################
    # Nano TDF - Data API
    #################################################

#    plain_text = 'Hello world!!'
#    sampleStringStorageNano = TDFStorageType()
#    sampleStringStorageNano.set_tdf_storage_string_type(plain_text)
#    nan_tdf_data = nano_tdf_client.encrypt_data(plain_text)
#
#    sampleEncryptedStringStorageNano = TDFStorageType()
#    sampleEncryptedStringStorageNano.set_tdf_storage_string_type(nan_tdf_data)
#    decrypted_plain_text = nano_tdf_client.decrypt_data(sampleEncrypteStringStorageNano)
#
#    if plain_text == decrypted_plain_text:
#        print("Nano TDF Encrypt/Decrypt is successful!!")
#    else:
#        print("Error: Nano TDF Encrypt/Decrypt failed!!")

except:
    print("Unexpected error: %s" % sys.exc_info()[0])
    raise
