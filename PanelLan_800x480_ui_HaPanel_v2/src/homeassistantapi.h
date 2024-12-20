
//WiFiClientSecure client;
#include <ArduinoJson.h> // include the ArduinoJson library
HTTPClient http;
String ha_token   = ha_pwd;

String getSensorValue(String entity)
{
    String api_url = ha_server + "/api/states/" + entity;
    http.begin(api_url);
    http.addHeader("Authorization", "Bearer " + ha_token);
    int code = http.GET();
    if (code != HTTP_CODE_OK)
    {
        Serial.println("Error '" + String(code) + "' connecting to HA API for: " + api_url);
        return "";
    }
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, http.getStream());
    http.end();
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "";
    }
    String state = doc["state"];
    Serial.println("  * " + entity);
    Serial.println("  - " + entity + " state: " + state);
    return state;
}

String getSensorAttributeValue(String entity, String attribute)
{
    String api_url = ha_server + "/api/states/" + entity;
    http.begin(api_url);
    http.addHeader("Authorization", "Bearer " + ha_token);
    int code = http.GET();
    if (code != HTTP_CODE_OK)
    {
        Serial.println("Error '" + String(code) + "' connecting to HA API for: " + api_url);
        return "";
    }
    DynamicJsonDocument doc(4096);
    DeserializationError error = deserializeJson(doc, http.getStream());
    http.end();

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return "";
    }
    // read attribute
    String attr = doc["attributes"][attribute];
    if (attr != NULL && attr != "" && attr != "null")
    {
        Serial.println("  - " + entity + ".Attributes[" + attribute + "]: " + attr);
        return attr;
    }
    // try entity properties
    String coreAttr = doc[attribute];
    if (coreAttr != NULL && coreAttr != "" && coreAttr != "null")
    {
        Serial.println("  - " + entity + "[" + attribute + "]: " + coreAttr);
        return coreAttr;
    }

    Serial.println("  - " + entity + ".Attributes[" + attribute + "]: " + attr);
    return "";
}
