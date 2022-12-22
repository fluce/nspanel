const char* preset_name_freeze="Hors gel";
const char* preset_name_auto="Auto";
int loop_control=0;
int try_mode=0;

int auto_trigger=0;
int master_trigger=0;
char auto_display[8]="      ";

int auto_mode=0;

void auto_refresh()
{
    ESP_LOGD("auto", "auto_trigger=%d", auto_trigger);
    int idx=0;
    for(int i=0;i<5;i++) 
    {
        auto_display[idx++]=((auto_trigger&(1<<i))?'a':'A')+i;
        if (idx==2) idx++;
    }
    id(disp1).send_command_printf("page0.auto_sources.txt=\"%s\"",auto_display);
}

const char* map_preset_to_component(const optional<ClimatePreset> preset, const optional<std::string> &preset_custom)
{
    if (preset.has_value())
    {
        switch(preset.value())
        {
            case climate::CLIMATE_PRESET_COMFORT: return "ps_comfort";
            case climate::CLIMATE_PRESET_BOOST: return "ps_boost";
            case climate::CLIMATE_PRESET_ECO: return "ps_eco";
            default: break;
        };
    }
    else
        if (preset_custom.has_value() && preset_custom.value()==preset_name_freeze) return "ps_freeze";
    else
        if (preset_custom.has_value() && preset_custom.value()==preset_name_auto) return "ps_auto";
    return 0;
}
