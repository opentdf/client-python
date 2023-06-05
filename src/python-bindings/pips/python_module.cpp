//
//  TDF SDK
//
//  Created by Sujan Reddy on 2019/03/04.
//  Copyright 2019 Virtru Corporation
//

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <sstream>

#include <nanotdf_client.h>
#include <nanotdf_dataset_client.h>
#include <tdf_client.h>
#include <tdf_assertion.h>
#include <oidc_credentials.h>
#include <version.h>

#define STRINGIFY(x) #x
using namespace pybind11::literals;

PYBIND11_MODULE(opentdf, tdf) {

    using namespace virtru;
    namespace py = pybind11;

    tdf.doc() = "Python bindings for the TDF SDK library";

    // Use the version number from VERSION
    tdf.attr("__version__") = opentdf_VERSION;

    py::enum_<LogLevel>(tdf, "LogLevel")
        .value("Trace", LogLevel::Trace)
        .value("Debug", LogLevel::Debug)
        .value("Info", LogLevel::Info)
        .value("Warn", LogLevel::Warn)
        .value("Error", LogLevel::Error)
        .value("Fatal", LogLevel::Fatal);

    py::enum_<AssertionType>(tdf, "AssertionType")
        .value("Handling", AssertionType::Handling)
        .value("Base", AssertionType::Base);

    py::enum_<Scope>(tdf, "Scope")
        .value("TDO", Scope::TDO)
        .value("PAYL", Scope::PAYL)
        .value("EXPLICIT", Scope::EXPLICIT)
        .value("Unknown", Scope::Unknown);

    py::enum_<AppliesToState>(tdf, "AppliesToState")
        .value("encrypted", AppliesToState::encrypted)
        .value("unencrypted", AppliesToState::unencrypted)
        .value("Unknown", AppliesToState::Unknown);

    py::enum_<StatementType>(tdf, "StatementType")
        .value("ReferenceStatement", StatementType::ReferenceStatement)
        .value("StructuredStatement", StatementType::StructuredStatement)
        .value("StringStatement", StatementType::StringStatement)
        .value("Base64BinaryStatement", StatementType::Base64BinaryStatement)
        .value("XMLBase64", StatementType::XMLBase64)
        .value("String", StatementType::String)
        .value("Unknow", StatementType::Unknow);


    py::class_<StatementGroup>(tdf, "StatementGroup")
        .def(py::init([](StatementType statementType) { 
                return new StatementGroup(statementType);}), R"pbdoc(
              Create an statement group
        )pbdoc")
        .def("set_statement_type", &StatementGroup::setStatementType,
                py::arg("statement_type"), R"pbdoc(
                Set the statement type for the statement group

            Args:
                statement_type(StatementType): The Statement type
        )pbdoc")
        .def("set_filename", &StatementGroup::setFilename,
                py::arg("filename"), R"pbdoc(
                Set the filename for the statement group

            Args:
                filename(String): The filename
        )pbdoc")
        .def("set_media_type", &StatementGroup::setMediaType,
                py::arg("media_type"), R"pbdoc(
                Set the media type for the statement group

            Args:
                media_type(String): Media type
        )pbdoc")
        .def("set_uri", &StatementGroup::setUri,
                py::arg("uri"), R"pbdoc(
                Set the uri for the statement group

            Args:
                uri(String): uri
        )pbdoc")
        .def("set_value", &StatementGroup::setValue,
                py::arg("value"), R"pbdoc(
                Set the value for the statement group

            Args:
                value(String): Value for the statement group
        )pbdoc")
        .def("set_is_encrypted", &StatementGroup::setIsEncrypted,
                py::arg("is_encrypted"), R"pbdoc(
                Set value for the isEncrypted flag for the statement group

            Args:
                is_encrypted(bool): is encrypted flag
        )pbdoc");


    py::class_<DefaultAssertion>(tdf, "DefaultAssertion")
        .def(py::init([](Scope scope) { 
                return new DefaultAssertion(scope);}), R"pbdoc(
              Create a default assertion
        )pbdoc")
        .def("set_id", &DefaultAssertion::setId,
                py::arg("id"), R"pbdoc(
                Set the id for the assertion

            Args:
                id(String): The assertion id
        )pbdoc")
        .def("set_type", &DefaultAssertion::setType,
                py::arg("type"), R"pbdoc(
                Return the type of the assertion

            Args:
                type(String): The type of the assetion
        )pbdoc")
        .def("set_statement_group", &DefaultAssertion::setStatementGroup,
                py::arg("statement_group"), R"pbdoc(
                Set the statement group for the assertion

            Args:
                statement_group(StatementGroup): Statement group
        )pbdoc")
        .def("set_statement_metadata", &DefaultAssertion::setStatementMetadata,
                py::arg("statement_metadata"), R"pbdoc(
                Set the statement metadata for the assertion

            Args:
                statement_metaData(strimg): statement metdata for the assertion
        )pbdoc");    
        
    py::class_<HandlingAssertion>(tdf, "HandlingAssertion")
        .def(py::init([](Scope scope) { 
                return new HandlingAssertion(scope);}), R"pbdoc(
              Create a handling assertion
        )pbdoc")
        .def("set_id", &HandlingAssertion::setId,
                py::arg("id"), R"pbdoc(
                Set the id for the handling assertion

            Args:
                id(String): The assertion id
        )pbdoc")
        .def("set_applied_to_state", &HandlingAssertion::setAppliesToState,
                py::arg("type"), R"pbdoc(
                Set the applied state for the assertion.

            Args:
                appled(AppliesToState): The applies to state
        )pbdoc")
        .def("set_handling_statement", &HandlingAssertion::setHandlingStatement,
                py::arg("handling_statement"), R"pbdoc(
                Set the handling statement for the assertion

            Args:
                handling_statement(strimg): statement metdata for the assertion
        )pbdoc"); 

    py::class_<OIDCCredentials>(tdf, "OIDCCredentials")
        .def(py::init([]() { return new OIDCCredentials();}), R"pbdoc(
              Create an OIDC credentials object
        )pbdoc")
        .def(py::init([](const std::string &openIDConfigurationUrl) {
            return new OIDCCredentials(openIDConfigurationUrl);}), R"pbdoc(
              Create an OIDC credentials object
        )pbdoc")
        .def("set_client_credentials_client_secret", &OIDCCredentials::setClientCredentialsClientSecret,
                py::arg("client_id"), py::arg("client_secret"),
                py::arg("organization_name"), py::arg("oidc_endpoint"), R"pbdoc(
                Set the client credentials that will be use for authz with OIDC server

            Args:
                client_id(string): The client id
                client_secret(string): The client secret
                organization_name(string): The OIDC realm or organization the client belongs to
                oidc_endpoint(string): The OIDC server url
        )pbdoc")
        .def("set_client_id_and_client_secret", &OIDCCredentials::setClientIdAndClientSecret,
                py::arg("client_id"), py::arg("client_secret"), R"pbdoc(
                Set the client credentials that will be use for authz with OIDC server

            Args:
                client_id(string): The client id
                client_secret(string): The client secret
        )pbdoc")
        .def("set_client_credentials_pki", &OIDCCredentials::setClientCredentialsPKI,
                py::arg("client_id"),
                py::arg("client_key_file_name"),
                py::arg("client_cert_file_name"),
                py::arg("certificate_authority"),
                py::arg("organization_name"), py::arg("oidc_endpoint"), R"pbdoc(
                Set the client credentials that will be use for authz with OIDC server

            Args:
                client_id(string): The client id
                client_key_file_name(string): The name of the file containing the client key
                client_cert_file_name(string): The name of the file containing the client certificate
                certificate_authority(string): The certificate authority to use
                organization_name(string): The OIDC realm or organization the client belongs to
                oidc_endpoint(string): The OIDC server url
        )pbdoc")
        .def("set_client_credentials_token_exchange", &OIDCCredentials::setClientCredentialsTokenExchange,
                py::arg("client_id"),
                py::arg("client_secret"),
                py::arg("external_exchange_token"),
                py::arg("organization_name"), py::arg("oidc_endpoint"), R"pbdoc(
                Set the client credentials that will be use for authz with OIDC server and external token.

            Args:
                client_id(string): The client id
                client_secret(string): The client secret
                external_exchange_token(string): The external token that will be processed and exchanged for a new one.
                organization_name(string): The OIDC realm or organization the client belongs to
                oidc_endpoint(string): The OIDC server url
        )pbdoc")        
        .def("set_client_id_and_pki", &OIDCCredentials::setClientIdAndPKI,
                py::arg("client_id"),
                py::arg("client_key_file_name"),
                py::arg("client_cert_file_name"),
                py::arg("certificate_authority"), R"pbdoc(
                Set the client credentials that will be use for authz with OIDC server

            Args:
                client_id(string): The client id
                client_key_file_name(string): The name of the file containing the client key
                client_cert_file_name(string): The name of the file containing the client certificate
                certificate_authority(string): The certificate authority to use
        )pbdoc")
        .def("get_client_id", &OIDCCredentials::getClientId, R"pbdoc(
            Return the client id.
        )pbdoc")
        .def("get_client_secret", &OIDCCredentials::getClientSecret, R"pbdoc(
            Return the client secret.
        )pbdoc")
        .def("get_username", &OIDCCredentials::getUsername, R"pbdoc(
            Return the username.
        )pbdoc")
        .def("get_password", &OIDCCredentials::getPassword, R"pbdoc(
            Return the password for associated user
        )pbdoc")
        .def("get_client_key_file_name", &OIDCCredentials::getClientKeyFileName, R"pbdoc(
            Return the name of the file containing the client key
        )pbdoc")
        .def("get_client_cert_file_name", &OIDCCredentials::getClientCertFileName, R"pbdoc(
            Return the name of the file containing the client certificate
        )pbdoc")
        .def("get_certificate_authority", &OIDCCredentials::getCertificateAuthority, R"pbdoc(
            Return the certificate authority
        )pbdoc")
        .def("get_org_name", &OIDCCredentials::getOrgName, R"pbdoc(
            Return the OIDC realm or organization the client belongs to
        )pbdoc")
        .def("get_oidc_endpoint", &OIDCCredentials::getOIDCEndpoint, R"pbdoc(
            Return the OIDC server url
        )pbdoc")
        .def("__repr__", [](const OIDCCredentials &oidcCredentials) {
            return oidcCredentials.str();
        });


        /*
                /// Add the handling assertion to the TDF
        /// \param handlingAssertion - The handling assertion object
        void setHandlingAssertion(const HandlingAssertion& handlingAssertion);

        /// Add the default assertion to the TDF
        /// \param defaultAssertion - The default assertion object
        void setDefaultAssertion(const DefaultAssertion& defaultAssertion);
        */

    py::class_<TDFStorageType>(tdf, "TDFStorageType")
            .def(py::init([]() { return new TDFStorageType();}), R"pbdoc(
              Create an TDF storage type
        )pbdoc")
        .def("set_tdf_storage_file_type", &TDFStorageType::setTDFStorageFileType,
                 py::arg("file_path"), R"pbdoc(
                set the TDF storage type as type file.

            Args:
                file_path(string): The file on which the tdf operations to be performed on
        )pbdoc")
        .def("set_tdf_storage_string_type", &TDFStorageType::setTDFStorageStringType,
                 py::arg("str"), R"pbdoc(
                set the TDF storage type as type string.

            Args:
                str(string): The str container containing data to be encrypted or decrypted
        )pbdoc")
        .def("set_tdf_storage_s3_type", &TDFStorageType::setTDFStorageS3Type,
                 py::arg("S3Url"), py::arg("awsAccessKeyId"), py::arg("awsSecretAccessKey"), py::arg("awsRegionName"), R"pbdoc(
                set the TDF storage type as type S3.

            Args:
                S3Url(string): https-prefixed URL to the object to be read
                awsAccessKeyID(string) - Access Key ID for the AWS credentials
                awsSecretAccessKey(string) - Secret access key for AWS credentials
                awsRegionName(string) - Region name for AWS credentials
        )pbdoc")
        .def("set_handling_assertion", &TDFStorageType::setHandlingAssertion,
                 py::arg("handling_assertion"), R"pbdoc(
                Set the handling assertion to the TDF

            Args:
                handlingAssertion(HandlingAssertion): The handling assertion object
        )pbdoc")
        .def("set_default_assertion", &TDFStorageType::setDefaultAssertion,
                 py::arg("default_assertion"), R"pbdoc(
                Set the default assertion to the TDF

            Args:
                default_assertion(DefaultAssertion): The default assertion object
        )pbdoc")
        .def("__repr__", [](const TDFStorageType &tdfStorageType) {
                return tdfStorageType.str();
        });

    // TDF Client python wrapper.
    // NOTE: Intentionally have long lines because sed script need to parse for arguments
    py::class_<TDFClient>(tdf, "TDFClient")
        .def(py::init([](const std::string &easUrl, const std::string &user) {
                 return new TDFClient(easUrl, user);
             }),
             py::arg("eas_url"), py::arg("user"), R"pbdoc(
              DEPRECATED - use OIDC constructors instead.
              Create an instance of Client.

              Args:
                 eas_url(string): The eas url.
                 user(string): The registered user on eas.

            )pbdoc")
        .def(py::init([](const std::string &backendUrl, const std::string &user, const std::string &clientKeyFileName, const std::string &clientCertFileName, const std::string &sdkConsumerCertAuthority) {
                 return new TDFClient(
                     backendUrl,
                     user,
                     clientKeyFileName,
                     clientCertFileName,
                     sdkConsumerCertAuthority);
             }),
             py::arg("backend_url"), py::arg("user"), py::arg("client_key_filename"), py::arg("client_cert_filename"), py::arg("sdk_consumer_certauthority"), R"pbdoc(
              Create an instance of Client.

              Args:
                 backend_url(string) - The EAS url
                 user(string): The registered user on eas.
                 client_key_fileName(string): Path to client key file.
                 client_cert_filename(string): Path to client certificate file.
                 sdk_consumer_certauthority(string): Path to cert authority file.
            )pbdoc")
        .def(py::init([](const OIDCCredentials& oidcCredentials, const std::string &kasUrl) {
                     return new TDFClient(oidcCredentials, kasUrl);
                 }),
                 py::arg("oidc_credentials"), py::arg("kas_url"), R"pbdoc(
              Create an instance of Client

              Args:
                 oidc_credentials(OIDCCredentials): OIDC credentials object
                 kas_url(string): The KAS backend url
            )pbdoc")
        .def("share_with_users", &TDFClient::shareWithUsers, py::arg("users_list"), R"pbdoc(
               Add access to the TDF file/data for the users in the list

              Args:
                 users_list(list): Share the TDF with the users in the list
            )pbdoc")
        .def("encrypt_file", [](TDFClient &tdfClient, const TDFStorageType &tdfStorageType, const std::string &outFile) { return tdfClient.encryptFile(tdfStorageType, outFile); }, py::arg("tdf_storage_type"), py::arg("out_filename"), R"pbdoc(
              Encrypt the file

              Args:
                 tdf_storage_type(TDFStorageType) - Type of the tdf
                 out_filename(string) - The encrypted file name.
            )pbdoc")
        .def("decrypt_file", [](TDFClient &tdfClient, const TDFStorageType &tdfStorageType, const std::string &outFile) { return tdfClient.decryptFile(tdfStorageType, outFile); }, py::arg("tdf_storage_type"), py::arg("out_filename"), R"pbdoc(
              Decrypt the file

              Args:
                 tdf_storage_type(TDFStorageType) - Type of the tdf
                 out_filename(string) - The decrypted file name.
            )pbdoc")
        .def("encrypt_data", [](TDFClient &tdfClient,  const TDFStorageType &tdfStorageType) {
                auto encryptedData = tdfClient.encryptData(tdfStorageType);
                return py::bytes(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
            }, py::arg("tdf_storage_type"), R"pbdoc(
              Encrypt the string

              Args:
                  tdf_storage_type(TDFStorageType) - Type of the tdf

              Returns:
                 TDF data.
            )pbdoc")
        .def("decrypt_data", [](TDFClient &tdfClient,  const TDFStorageType &tdfStorageType) {
                auto plainData = tdfClient.decryptData(tdfStorageType);
                return std::string(plainData.begin(), plainData.end());
        }, py::arg("tdf_storage_type"), R"pbdoc(
              Decrypt the TDF data

              Args:
                  tdf_storage_type(TDFStorageType) - Type of the tdf

              Returns:
                 Plain data.
            )pbdoc")
        .def("decrypt_data_partial", [](TDFClient &tdfClient, const TDFStorageType &tdfStorageType, size_t offset, size_t length){
             auto plainData = tdfClient.decryptDataPartial(tdfStorageType, offset, length);
             return std::string(plainData.begin(), plainData.end());
             }, py::arg("tdf_storage_type"), py::arg("offset"), py::arg("length"), R"pbdoc(
             Decrypt part of the data of tdf storage type.

             Args:
                tdf_storage_type(TDFStorageType) - Type of the tdf
                offset(int) - Start position within the plaintext to be decrypted
                length(int) - length of the plaintext to be decrypted

             Returns:
                Plain data.
            )pbdoc")
        .def("enable_console_logging", &TDFClient::enableConsoleLogging, py::arg("log_level"), R"pbdoc(
              Enable the logger to write logs to the console

              Note: The default is LogLevel::Warn

              Args:
                 log_level(LogLevel): The log level

            )pbdoc")
        .def("enable_benchmark", &TDFClient::enableBenchmark, R"pbdoc(
              Enable benchmark logging
            )pbdoc")     
        .def("set_xml_format", &TDFClient::setXMLFormat, R"pbdoc(
              Create TDFs in XML format instead of zip format.
            )pbdoc")
        .def("subject_attributes", &TDFClient::getSubjectAttributes, R"pbdoc(
              Get subject attributes

              Returns:
                 Subject attribute URIs.
            )pbdoc")
        .def("get_policy", &TDFClient::getPolicy, py::arg("tdf_data"), R"pbdoc(
              Gets the policy object (as a JSON string) of the provided TDF data

              Args:
                 tdf_data(string) - Encrypted TDF data.

              Returns:
                 JSON string representing a TDF Policy Object.
            )pbdoc")
        .def("set_encrypted_metadata", &TDFClient::setEncryptedMetadata, py::arg("metadata"), R"pbdoc(
              Assign the metadata that will be encrypted and stored in the TDF, separately from the data

              Args:
                 metadata(string) - The metadata that is stored in the tdf
            )pbdoc")
        .def("get_encrypted_metadata", &TDFClient::getEncryptedMetadata, py::arg("tdf_data"), R"pbdoc(
              Decrypt and return TDF metadata as a string. If the TDF content has no encrypted metadata, will return an empty string.

              Args:
                 tdf_data(string) - The string containing a tdf data.

              Returns:
                  The string containing the metadata.
            )pbdoc")
        .def("add_data_attribute", &TDFClient::addDataAttribute, py::arg("data_attribute"), py::arg("kas_url"), R"pbdoc(
               Add data attribute

              Args:
                 data_attribute(string): Add a data attribute to the TDF policy. Should be a URI.
                 kas_url(string): URL of the KAS instance this attribute is associated with.
            )pbdoc")
        .def_static("is_file_tdf", &TDFClient::isFileTDF, py::arg("in_filename"), R"pbdoc(
               Check if file is TDF

              Args:
                 in_filename(string) - The file to be checked.

                Returns:
                    True is file is TDF, False otherwise
            )pbdoc")
        .def_static("is_data_tdf", &TDFClient::isStringTDF, py::arg("tdf_data"), R"pbdoc(
               Check if data is TDF

              Args:
                 tdf_data(string) - The data to be checked.
                 
                Returns:
                    True is data is TDF, False otherwise
            )pbdoc");

    // Nano TDF Client python wrapper.
    // NOTE: Intentionally have long lines because sed script need to parse for arguments
    py::class_<NanoTDFClient>(tdf, "NanoTDFClient")
        .def(py::init([]() { return new NanoTDFClient(); }), R"pbdoc(
              Create an instance of nano tdf client.
              NOTE: should me used for only offline decrypt operation.
            )pbdoc")
        .def(py::init([](const std::string &easUrl, const std::string &user) {
                 return new NanoTDFClient(easUrl, user);
             }),
             py::arg("eas_url"), py::arg("user"), R"pbdoc(
              Create an instance of nano tdf client.

              Args:
                 eas_url(string): The eas url.
                 user(string): The registered user on eas.

            )pbdoc")
        .def(py::init([](const std::string &easUrl, const std::string &user, const std::string &clientKeyFileName, const std::string &clientCertFileName, const std::string &sdkConsumerCertAuthority) {
                 return new NanoTDFClient(easUrl, user, clientKeyFileName, clientCertFileName, sdkConsumerCertAuthority);
             }),
             py::arg("eas_url"), py::arg("user"), py::arg("clientKeyFileName"), py::arg("clientCertFileName"), py::arg("sdkConsumerCertAuthority"), R"pbdoc(
              Create an instance of nano tdf client.

              Args:
                 eas_url(string): The eas url.
                 user(string): The registered user on eas.
                 clientKeyFileName(string): Path to client key file.
                 clientCertFileName(string): Path to client certificate file.
                 sdkConsumerCertAuthority(string): Path to cert authority file.
            )pbdoc")
        .def(py::init([](const OIDCCredentials& oidcCredentials, const std::string &kasUrl) {
                     return new NanoTDFClient(oidcCredentials, kasUrl);
                 }),
                 py::arg("oidc_credentials"), py::arg("kas_url"), R"pbdoc(
              Create an instance of Client

              Args:
                 oidc_credentials(OIDCCredentials): OIDC credentials object
                 kas_url(string): The KAS backend url
        )pbdoc")
        .def_static("is_valid_nano_tdf_file", &NanoTDFClient::isValidNanoTDFFile,  py::arg("in_filename") ,R"pbdoc(
               Check if the file is in valid NanoTDF format.

              Args:
                 in_filename(string) - The NanoTDF file
            )pbdoc")
        .def_static("is_valid_nano_tdf_data", &NanoTDFClient::isValidNanoTDFData,  py::arg("tdf_data") ,R"pbdoc(
               Check if the data is in valid NanoTDF format.

              Args:
                 tdf_data(string) - The NanoTDF data
            )pbdoc")
        .def("share_with_users", &NanoTDFClient::shareWithUsers, py::arg("users_list"), R"pbdoc(
               Add access to the TDF file/data for the users in the list

              Args:
                 users_list(list): Share the TDF with the users in the list
            )pbdoc")
        .def("encrypt_file", [](NanoTDFClient &nanoTdfClient, const TDFStorageType &tdf_storage_type, const std::string &outFile) { return nanoTdfClient.encryptFile(tdf_storage_type, outFile); }, py::arg("tdf_storage_type"), py::arg("out_filename"), R"pbdoc(
              Encrypt the file

              Args:
                 tdf_storage_type(TDFStorageType) - Type of the tdf
                 out_filename(string) - The encrypted file name.

            )pbdoc")
        .def("decrypt_file", [](NanoTDFClient &nanoTdfClient, const TDFStorageType &tdf_storage_type, const std::string &outFile) { return nanoTdfClient.decryptFile(tdf_storage_type, outFile); }, py::arg("tdf_storage_type"), py::arg("out_filename"), R"pbdoc(
              Decrypt the file

              Args:
                 tdf_storage_type(TDFStorageType) - Type of the tdf
                 out_filename(string) - The decrypted file name.

            )pbdoc")
        .def(
             "decrypt_file_using_old_format", [](NanoTDFClient &nanoTdfClient, const std::string &inputFile, const std::string &outFile) { return nanoTdfClient.decryptFileUsingOldFormat(inputFile, outFile); }, py::arg("in_filename"), py::arg("out_filename"), R"pbdoc(
              Encrypt the file that are encrypted using old version of SDKs

              Args:
                 in_filename(string) - The file to be decrypted.
                 out_filename(string) - The decrypted file name.

            )pbdoc")
        .def("encrypt_data", [](NanoTDFClient &nanoTdfClient, const TDFStorageType &tdf_storage_type) {
                auto encryptedData = nanoTdfClient.encryptData(tdf_storage_type);
                return py::bytes(reinterpret_cast<const char*>(encryptedData.data()), encryptedData.size());
            }, py::arg("plain_text"), R"pbdoc(
              Encrypt the string

              Args:
                 tdf_storage_type(TDFStorageType) - Type of the tdf

              Returns:
                 TDF data.
            )pbdoc")
	.def("decrypt_data", [](NanoTDFClient &nanoTdfClient, const TDFStorageType &tdf_storage_type) {
              auto decryptedData = nanoTdfClient.decryptData(tdf_storage_type);
              return py::bytes(reinterpret_cast<const char*>(decryptedData.data()), decryptedData.size()); }, py::arg("tdf_storage_type"), R"pbdoc(
              Decrypt the TDF data

              Args:
                  tdf_storage_type(TDFStorageType) - Type of the tdf

              Returns:
                 Plain data.
            )pbdoc")
        .def(
             "decrypt_string_using_old_format", [](NanoTDFClient &nanoTdfClient, const std::string &tdfData) { return py::bytes(nanoTdfClient.decryptStringUsingOldFormat(tdfData)); }, py::arg("tdf_data"), R"pbdoc(
              Decrypt the TDF data that are encrypted using old version of SDKs

              Args:
                 tdf_data(string) - TDF data to be decrypted.

              Returns:
                 Plain data.
            )pbdoc")
        .def("validate_signature", &NanoTDFClient::validateSignature, py::arg("signer_public_key"), R"pbdoc(
              Validate the TDF on decrypt(check if the TDF is singed by right entity).
              Throws exception on decrypt if the given public key doesn't match the one in TDF.

              Args:
                 signer_public_key(string): The PEM-encoded public key as a string.
            )pbdoc")
        .def(
            "set_entity_private_key", [](NanoTDFClient &nanoTdfClient, const std::string &entityPrivateKey) { nanoTdfClient.setEntityPrivateKey(entityPrivateKey, EllipticCurve::SECP256R1); }, py::arg("entity_private_key"), R"pbdoc(
              Set the entity private key(In PEM format), which will be used by this SDK for encryption/decryption of
              the payload/policy

              NOTE: The private key should be from curve secp256r1

              Args:
                 entity_private_key(string): The PEM-encoded private key as a string.
            )pbdoc")
        .def(
            "set_signer_private_key", [](NanoTDFClient &nanoTdfClient, const std::string &signerPrivateKey) { nanoTdfClient.setSignerPrivateKey(signerPrivateKey, EllipticCurve::SECP256R1); }, py::arg("signer_private_key"), R"pbdoc(
              Set the signer private key(In PEM format). Calling this method enables the signature entry in nano tdf

              NOTE: The private key should be from curve secp256r1

              Args:
                 signer_private_key(string): The PEM-encoded private key as a string.
            )pbdoc")
        .def("set_decrypter_public_key", &NanoTDFClient::setDecrypterPublicKey, py::arg("decrypter_public_key"), R"pbdoc(
              Set the kas decrypter public-key(In PEM format). This can be used for offline mode.

              NOTE: The public key should be from curve secp256r1

              Args:
                 decrypter_public_key(string): The PEM-encoded public key as a string.
            )pbdoc")
        .def(
            "get_entity_private_key", [](NanoTDFClient &nanoTdfClient) {
                auto keyAndCurve = nanoTdfClient.getEntityPrivateKeyAndCurve(); return keyAndCurve.first; }, R"pbdoc(
              Return the entity private key in PEM format.

              Returns:
                 The entity private key in PEM format.
            )pbdoc")
        .def("enable_console_logging", &NanoTDFClient::enableConsoleLogging, py::arg("log_level"), R"pbdoc(
              Enable the logger to write logs to the console

              Note: The default is LogLevel::Warn

              Args:
                 log_level(LogLevel): The log level
            )pbdoc")
        .def("enable_benchmark", &NanoTDFClient::enableBenchmark, R"pbdoc(
              Enable benchmark logging
            )pbdoc")    
        .def("subject_attributes", &NanoTDFClient::getSubjectAttributes, R"pbdoc(
              Get subject attributes

              Returns:
                 Subject attribute URIs.
            )pbdoc")
        .def("add_data_attribute", &NanoTDFClient::addDataAttribute, py::arg("data_attribute"), py::arg("kas_url"), R"pbdoc(
               Add data attribute

              Args:
                 data_attribute(string): Add a data attribute to the TDF policy. Should be a URI.
                 kas_url(string): URL of the KAS instance this attribute is associated with.
            )pbdoc");

    // Nano TDF Client python wrapper.
    // NOTE: Intentionally have long lines because sed script need to parse for arguments
    py::class_<NanoTDFDatasetClient>(tdf, "NanoTDFDatasetClient")
        .def(py::init([](uint32_t maxKeyIterations) { return new NanoTDFDatasetClient(maxKeyIterations); }),
             py::arg("max_key_iterations") = kNTDFMaxKeyIterations, R"pbdoc(
              Create an instance of nano tdf dataset client.

              Args:
                 max_key_iterations(int) - Maximum number of encrypt operations before a new key is generated.(default is 8388607).

              NOTE: should me used for only offline decrypt operation.
            )pbdoc")
        .def(py::init([](const std::string &easUrl, const std::string &user, uint32_t maxKeyIterations) {
                 return new NanoTDFDatasetClient(easUrl, user, maxKeyIterations);
             }),
             py::arg("eas_url"), py::arg("user"), py::arg("max_key_iterations") = kNTDFMaxKeyIterations, R"pbdoc(
              Create an instance of nano tdf dataset client.

              Args:
                 eas_url(string): The eas url.
                 user(string): The registered user on eas.
                 max_key_iterations(int) - Maximum number of encrypt operations before a new key is generated.(default is 8388607).

            )pbdoc")
        .def(py::init([](const std::string &easUrl, const std::string &user, const std::string &clientKeyFileName,
                         const std::string &clientCertFileName, const std::string &sdkConsumerCertAuthority, uint32_t maxKeyIterations) {
                 return new NanoTDFDatasetClient(easUrl, user, clientKeyFileName, clientCertFileName, sdkConsumerCertAuthority, maxKeyIterations);
             }),
             py::arg("eas_url"), py::arg("user"), py::arg("clientKeyFileName"), py::arg("clientCertFileName"),
             py::arg("sdkConsumerCertAuthority"), py::arg("max_key_iterations") = kNTDFMaxKeyIterations, R"pbdoc(
              Create an instance of nano tdf client.

              Args:
                 eas_url(string): The eas url.
                 user(string): The registered user on eas.
                 clientKeyFileName(string): Path to client key file.
                 clientCertFileName(string): Path to client certificate file.
                 sdkConsumerCertAuthority(string): Path to cert authority file.
                 max_key_iterations(int) - Maximum number of encrypt operations before a new key is generated.(default is 8388607).
            )pbdoc")
        .def(py::init([](const OIDCCredentials& oidcCredentials, const std::string &kasUrl,
                         uint32_t maxKeyIterations) {
                     return new NanoTDFDatasetClient(oidcCredentials, kasUrl, maxKeyIterations);
             }),
             py::arg("oidc_credentials"),
             py::arg("kas_url"),
             py::arg("max_key_iterations") = kNTDFMaxKeyIterations, R"pbdoc(
                
             Create an instance of nano tdf dataset client.
              Args:
                 oidc_credentials(OIDCCredentials): OIDC credentials object
                 kas_url(string): The KAS backend url
                 max_key_iterations(int) - Maximum number of encrypt operations before a new key is generated.(default is 8388607).
            )pbdoc") 
        .def("share_with_users", &NanoTDFDatasetClient::shareWithUsers, py::arg("users_list"), R"pbdoc(
               Add access to the TDF file/data for the users in the list

              Args:
                 users_list(list): Share the TDF with the users in the list
            )pbdoc")
        .def(
            "encrypt_file", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &inputFile, const std::string &outFile) { return nanoTdfDatasetClient.encryptFile(inputFile, outFile); }, py::arg("in_filename"), py::arg("out_filename"), R"pbdoc(
              Encrypt the file

              Args:
                 in_filename(string) - The file to be encrypted.
                 out_filename(string) - The encrypted file name.

            )pbdoc")
        .def(
            "decrypt_file", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &inputFile, const std::string &outFile) { return nanoTdfDatasetClient.decryptFile(inputFile, outFile); }, py::arg("in_filename"), py::arg("out_filename"), R"pbdoc(
              Encrypt the file

              Args:
                 in_filename(string) - The file to be decrypted.
                 out_filename(string) - The decrypted file name.

            )pbdoc")
        .def(
            "encrypt_string", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &str) {
                const auto& data = nanoTdfDatasetClient.encryptString(str);
                return py::bytes(reinterpret_cast<const char*>(data.data()), data.size()); }, py::arg("plain_text"), R"pbdoc(
              Encrypt the string

              Args:
                 plain_text(string) - Plain text to be encrypted.

              Returns:
                 TDF data.
            )pbdoc")
        .def(
            "decrypt_string", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &tdfData) {
                const auto& data = nanoTdfDatasetClient.decryptString(tdfData);
                return py::bytes(data.data(), data.size()); }, py::arg("tdf_data"), R"pbdoc(
              Decrypt the TDF data

              Args:
                 tdf_data(string) - TDF data to be decrypted.

              Returns:
                 Plain data.
            )pbdoc")
        .def("validate_signature", &NanoTDFDatasetClient::validateSignature, py::arg("signer_public_key"), R"pbdoc(
              Validate the TDF on decrypt(check if the TDF is singed by right entity).
              Throws exception on decrypt if the given public key doesn't match the one in TDF.

              Args:
                 signer_public_key(string): The PEM-encoded public key as a string.
            )pbdoc")
        .def(
            "set_entity_private_key", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &entityPrivateKey) { nanoTdfDatasetClient.setEntityPrivateKey(entityPrivateKey, EllipticCurve::SECP256R1); }, py::arg("entity_private_key"), R"pbdoc(
              Set the entity private key(In PEM format), which will be used by this SDK for encryption/decryption of
              the payload/policy

              NOTE: The private key should be from curve secp256r1

              Args:
                 entity_private_key(string): The PEM-encoded private key as a string.
            )pbdoc")
        .def(
            "set_signer_private_key", [](NanoTDFDatasetClient &nanoTdfDatasetClient, const std::string &signerPrivateKey) { nanoTdfDatasetClient.setSignerPrivateKey(signerPrivateKey, EllipticCurve::SECP256R1); }, py::arg("signer_private_key"), R"pbdoc(
              Set the signer private key(In PEM format). Calling this method enables the signature entry in nano tdf

              NOTE: The private key should be from curve secp256r1

              Args:
                 signer_private_key(string): The PEM-encoded private key as a string.
            )pbdoc")
        .def("set_decrypter_public_key", &NanoTDFDatasetClient::setDecrypterPublicKey, py::arg("decrypter_public_key"), R"pbdoc(
              Set the kas decrypter public-key(In PEM format). This can be used for offline mode.

              NOTE: The public key should be from curve secp256r1

              Args:
                 decrypter_public_key(string): The PEM-encoded public key as a string.
            )pbdoc")
        .def(
            "get_entity_private_key", [](NanoTDFDatasetClient &nanoTdfDatasetClient) {
                auto keyAndCurve = nanoTdfDatasetClient.getEntityPrivateKeyAndCurve(); return keyAndCurve.first; }, R"pbdoc(
              Return the entity private key in PEM format.

              Returns:
                 The entity private key in PEM format.
            )pbdoc")
        .def("enable_console_logging", &NanoTDFDatasetClient::enableConsoleLogging, py::arg("log_level"), R"pbdoc(
              Enable the logger to write logs to the console

              Note: The default is LogLevel::Warn

              Args:
                 log_level(LogLevel): The log level
            )pbdoc")
        .def("add_data_attribute", &NanoTDFDatasetClient::addDataAttribute, py::arg("data_attribute"), py::arg("kas_url"), R"pbdoc(
               Add data attribute

              Args:
                 data_attribute(string): Add a data attribute to the TDF policy. Should be a URI.
                 kas_url(string): URL of the KAS instance this attribute is associated with.
            )pbdoc");
}
