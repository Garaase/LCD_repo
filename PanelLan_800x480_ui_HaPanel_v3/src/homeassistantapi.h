
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

String getLightValue(String entity)
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
    String red = doc["attributes"]["rgb_color"][0];
    String green = doc["attributes"]["rgb_color"][1];
    String blue = doc["attributes"]["rgb_color"][2];
    String color = String( red+","+ green+","+ blue);
    Serial.println("  * " + entity);
    Serial.println("  - " + entity + " red: " + color);
    return color;
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

void setWebhookLightstripValues(char valueType, int brghtnssValue, int colortemp)
{
    int code =  0;
    String api_url;
    if (valueType == 1)
    {
        api_url = ha_server + "/api/webhook/lightstripbrightness";
        http.begin(api_url);
        http.addHeader("Content-Type", "application/json");
        http.POST("{\"brightness\": "+String(brghtnssValue)+"}");
        delay(2);
    }
    else if (valueType == 2)
    {
        api_url = ha_server + "/api/webhook/lightstripcolortemp";
        http.begin(api_url);
        http.addHeader("Content-Type", "application/json");
        http.POST("{\"color_temp\":"+String(colortemp)+"}");
        delay(2);
    }
    else
    {
        // Do nothing
    }        

    if (code != HTTP_CODE_OK)
    {
        Serial.println("Error '" + String(code) + "' connecting to HA API for: " + api_url);
    }
}

void setWebhookrbgLampValues(char valueType, int brghtnssValue, lv_color32_t col)
{
    int code =  0;
    String api_url;
    if (valueType == 1)
    {
        api_url = ha_server + "/api/webhook/rgblamp1brightness";
        http.begin(api_url);
        http.addHeader("Content-Type", "application/json");
        http.POST("{\"brightness\": "+String(brghtnssValue)+"}");
        delay(2);
    }
    else if (valueType == 2)
    {
        api_url = ha_server + "/api/webhook/rgblamp1color";
        http.begin(api_url);
        http.addHeader("Content-Type", "application/json");
        http.POST("{\"rgb_color\":["+String(col.ch.red)+","+String(col.ch.green)+","+String(col.ch.blue)+"]}");
        delay(2);
    }
    else
    {
        // Do nothing
    } 
}

void setWebhookSwitches(const char* _switch)
{
    String api_url = ha_server + "/api/webhook/"+_switch;
    http.begin(api_url);
    int code = http.POST("");
    if (code != HTTP_CODE_OK)
    {
        Serial.println("Error '" + String(code) + "' connecting to HA API for: " + api_url);
    }
}