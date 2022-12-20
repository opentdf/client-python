# OpenTDF SDK

The OpenTDF Python SDK allows developers to easily create and manage encrypted [Trusted Data Format (TDF) objects](https://github.com/opentdf/spec) and interact with [Key Access and Attribute Provider services (KAS, AP).](https://github.com/opentdf/spec/tree/main/protocol)

## Installation

Upgrade pip3 to the latest version and run

```shell
pip3 install opentdf
```

## Backend services

To perform any TDF operation, first start the backend services. [Follow the opentdf backend instructions here](https://github.com//opentdf/documentation/tree/main//quickstart) to get going quickly.

## Authentication 

The OpenTDF team has chosen [Keycloak](https://www.keycloak.org) as its reference implementation IdP.

The OpenTDF SDK uses OIDC as authentication and authorization to verify the client has access on behalf of an entity or the a certain level of access appropriate to its subject attributes. The opentdf SDK currently supports only client attributes, not user or person entity attributes. First, [create a client application in keycloak](https://www.keycloak.org/docs/latest/authorization_services/#_resource_server_create_client)

Use the client creds to create an `OIDCCredentials` instance and pass into the `TDFClient` or `NanoTDFClient`. With the client initialized as such, you can use it  to perform encrypt/decrypt operations on behalf of the assigned client profile.

## Access control

OpenTDF enables the access control of the data by enabling attributes. The key access ABAC backend service can be used to add and remove attribute values to the client application.

Applying a data attribute to the TDF can be done using this SDK api.

```python
client.add_data_attribute("https://example.com/attr/Classification/value/S", "optionalKasUrl")
```


## Create TDF Object (minimal example)

```python
import sys
from opentdf import TDFClient, NanoTDFClient, OIDCCredentials, LogLevel, TDFStorageType

# encrypt the file and apply the policy on tdf file and also decrypt.
OIDC_ENDPONT = "http://localhost:65432/"
KAS_URL = "http://localhost:65432/api/kas"
OIDC_CONFIGURATION_URL = "http://localhost:65432/auth/realms/tdf/.well-known/openid-configuration"
try:
    # Create OIDC credentials object
    oidc_creds = OIDCCredentials(OIDC_CONFIGURATION_URL)
    oidc_creds.set_client_id_and_client_secret(client_id = "tdf-client",
                                 client_secret = "123-456")

    client = TDFClient(oidc_credentials = oidc_creds,
                        kas_url = KAS_URL)
    client.enable_console_logging(LogLevel.Warn)

    #################################################
    # TDF - File API
    ################################################


    client.add_data_attribute("https://example.com/attr/Classification/value/S", KAS_URL)

    # NOTE: Make sure sample.txt file exists
    
    sampleTxtStorage = TDFStorageType()
    sampleTxtStorage.set_tdf_storage_file_type("sample.txt")
    client.enable_benchmark()
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
    nano_tdf_client.enable_benchmark()

    sampleTxtStorageNano = TDFStorageType()
    sampleTxtStorageNano.set_tdf_storage_file_type("sample.txt")
    nano_tdf_client.encrypt_file(sampleTxtStorageNano, "sample.txt.ntdf")

    sampleTdfStorageNano = TDFStorageType()
    sampleTdfStorageNano.set_tdf_storage_file_type("sample.txt.ntdf")
    nano_tdf_client.decrypt_file(sampleTdfStorageNano, "sample_out.nano.txt")

    #################################################
    # Nano TDF - Data API
    #################################################

    plain_text = 'Hello world!!'
    sampleStringStorageNano = TDFStorageType()
    sampleStringStorageNano.set_tdf_storage_string_type(plain_text)
    nan_tdf_data = nano_tdf_client.encrypt_data(sampleStringStorageNano)

    sampleEncryptedStringStorageNano = TDFStorageType()
    sampleEncryptedStringStorageNano.set_tdf_storage_string_type(nan_tdf_data)
    decrypted_plain_text = nano_tdf_client.decrypt_data(sampleEncryptedStringStorageNano)

    if plain_text == decrypted_plain_text.decode("utf-8"):
        print("Nano TDF Encrypt/Decrypt is successful!!")
    else:
        print("Error: Nano TDF Encrypt/Decrypt failed!!")

except:
    print("Unexpected error: %s" % sys.exc_info()[0])
    raise
```

## License
OpenTDF is licensed under the Clear BSD License.

See the [LICENSE](https://github.com/opentdf/client-cpp/blob/main/LICENSE) file for more details.

[Terms of Service](https://www.virtru.com/terms-of-service/)

[Privacy Policy](https://www.virtru.com/privacy-policy/)
