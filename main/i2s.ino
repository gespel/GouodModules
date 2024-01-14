void setup_i2n() {
    i2s_config_t i2s_config = {
      .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
      .sample_rate = sampleRate,
      .bits_per_sample = (i2s_bits_per_sample_t)bitDepth,
      .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
      .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),
      .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
      .dma_buf_count = 12,
      .dma_buf_len = 1024,
      .use_apll = true,
      .tx_desc_auto_clear = true,
    };
    
    i2s_pin_config_t pin_config = {
      .bck_io_num = 26, // BCLK-Pin
      .ws_io_num = 25, // LRCLK-Pin
      .data_out_num = 22, // Daten-Ausgangspins
      .data_in_num = I2S_PIN_NO_CHANGE, // Daten-Eingangspins (kein Eingang)
    };

    i2s_driver_install((i2s_port_t)i2sChannel, &i2s_config, 0, NULL);
    i2s_set_pin((i2s_port_t)i2sChannel, &pin_config);
}