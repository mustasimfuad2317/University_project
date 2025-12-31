#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <ctype.h>
// #include <glib.h>

//------ My Header Files ----------//
#include "System_info.h"
#include"terminal.h"
#include"sms_start.h"
#include"ai.h"
#include"reminder.h"
#include"shortcuts.h"



/*###############################################################################*/
/* ------------------------------ System Info Window -------------------------- */
/*##############################################################################*/




GtkTextBuffer *system_text_buffer = NULL;

// --- Function to load file and update text ---

static void load_system_report(void)
{
    FILE *file;
    char data[8192];

    file = fopen("system_report.txt", "r");
    if (!file)
    {
        gtk_text_buffer_set_text(system_text_buffer,
                                 "Error: system_report.txt not found!",
                                 -1);
        return;
    }

    size_t bytes = fread(data, 1, sizeof(data) - 1, file);
    data[bytes] = '\0';
    fclose(file);

    gtk_text_buffer_set_text(system_text_buffer, data, -1);
}

static void system_button_clicked(GtkWidget *widget, gpointer data)
{
    show_cpu_info();
    load_system_report();
}

static void os_info(GtkWidget *widget, gpointer data)
{
    show_os_info();
    load_system_report();
}

static void cpu_info(GtkWidget *widget, gpointer data)
{
    show_cpu_info();
    load_system_report();
}

static void ram_info(GtkWidget *widget, gpointer data)
{
    show_ram_info();
    load_system_report();
}

static void storage_info(GtkWidget *widget, gpointer data)
{
    show_storage_info();
    load_system_report();
}

static void network_info(GtkWidget *widget, gpointer data)
{
    show_network_info();
    load_system_report();
}

static void gpu_info(GtkWidget *widget, gpointer data)
{
    show_gpu_info();
    load_system_report();
}


static void uptime_info(GtkWidget *widget, gpointer data)
{
    show_running_processes();
    load_system_report();
}

static void clear_text(GtkWidget *widget, gpointer data)
{
    clearFile("system_report.txt");
    load_system_report();
}

static void save_info(GtkWidget *widget, gpointer data)
{
    save_report_to_file();
    load_system_report();
}

static void exit_system_win(GtkWidget *widget, gpointer data)
{
    GtkWidget *window = GTK_WIDGET(data);
    gtk_window_close(GTK_WINDOW(window));
}





static void create_system_win(GtkApplication *app)
{
    GtkWidget *system_win;
    GtkWidget *main_box;
    GtkWidget *left_box;
    GtkWidget *right_box;

    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *button5;
    GtkWidget *button6;
    GtkWidget *button7;
    GtkWidget *button8;
    GtkWidget *button9;
    GtkWidget *button10;

    GtkWidget *scrolled_win;
    GtkWidget *text_view;
    GtkTextBuffer *buffer;

    /* Window */
    system_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(system_win), "System Info");
    gtk_window_set_default_size(GTK_WINDOW(system_win), 700, 400);

    /* Main horizontal box */
    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    gtk_container_add(GTK_CONTAINER(system_win), main_box);

    /* Left vertical box (buttons) */
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), left_box, FALSE, FALSE, 5);

    /* Right box (text output) */
    right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), right_box, TRUE, TRUE, 5);

    /* Buttons */
    button1  = gtk_button_new_with_label("My OS");
    button2  = gtk_button_new_with_label("CPU");
    button3  = gtk_button_new_with_label("Ram");
    button4  = gtk_button_new_with_label("Storage");
    button5  = gtk_button_new_with_label("Network");
    button6  = gtk_button_new_with_label("GPU");
    button7  = gtk_button_new_with_label("UP Time");
    button8  = gtk_button_new_with_label("Save");
    button9  = gtk_button_new_with_label("Clear");
    button10 = gtk_button_new_with_label("Exit");



    g_signal_connect(button1, "clicked", G_CALLBACK(os_info), NULL);
    g_signal_connect(button2, "clicked", G_CALLBACK(cpu_info), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(ram_info), NULL);
    g_signal_connect(button4, "clicked", G_CALLBACK(storage_info), NULL);
    g_signal_connect(button5, "clicked", G_CALLBACK(network_info), NULL);
    g_signal_connect(button6, "clicked", G_CALLBACK(gpu_info), NULL);
    g_signal_connect(button7, "clicked", G_CALLBACK(uptime_info), NULL);
    g_signal_connect(button8, "clicked", G_CALLBACK(save_info), NULL);
    g_signal_connect(button9, "clicked", G_CALLBACK(clear_text), NULL);
    g_signal_connect(button10, "clicked", G_CALLBACK(exit_system_win), system_win);



    gtk_box_pack_start(GTK_BOX(left_box), button1,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button2,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button3,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button4,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button5,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button6,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button7,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button8,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button9,  FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), button10, FALSE, FALSE, 0);

    /* Scrollable text view */
    scrolled_win = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_win),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_box_pack_start(GTK_BOX(right_box), scrolled_win, TRUE, TRUE, 0);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);
    gtk_container_add(GTK_CONTAINER(scrolled_win), text_view);

    /* Save buffer globally */
    system_text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    gtk_text_buffer_set_text(system_text_buffer,
        "Click any button to load system report...",
        -1);

    gtk_widget_show_all(system_win);
}

/*############################# System Info End ########################################*/









/*###############################################################################*/
/* ------------------------------ Reminder Window -------------------------- */
/*##############################################################################*/


/* ---------------- Save reminder to file ---------------- */
void save_reminder_to_file(const char *text)
{
    FILE *fp = fopen("reminders.txt", "a");  // append mode
    if (!fp) return;

    fprintf(fp, "%s\n", text);
    fclose(fp);
}

/* ---------------- Reminder widgets struct ---------------- */
typedef struct {
    GtkWidget *year;     // Calendar widget
    GtkWidget *month;    // Reuse calendar
    GtkWidget *day;      // Reuse calendar
    GtkWidget *hour;
    GtkWidget *minute;
    GtkWidget *textview;
} ReminderWidgets;

/* ---------------- Save button callback ---------------- */
static void save_reminder(GtkWidget *widget, gpointer data)
{
    ReminderWidgets *rw = (ReminderWidgets *)data;

    /* --- Get date from calendar --- */
    guint year, month, day;
    gtk_calendar_get_date(GTK_CALENDAR(rw->year), &year, &month, &day);
    month += 1; // GTK months are 0-based

    /* --- Get hour and minute from combo boxes --- */
    const char *hour   = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rw->hour));
    const char *minute = gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(rw->minute));

    /* --- Get reminder message --- */
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(rw->textview));
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    char *message = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    /* --- Build final text --- */
    char final_text[512];
    snprintf(final_text, sizeof(final_text),
             "%04u %02u %02u %s %s | %s",
             year, month, day, hour, minute, message);

    /* --- Save to file --- */
    save_reminder_to_file(final_text);

    g_free(message);
}

/* ---------------- Reminder Window ---------------- */
static void create_reminder_win(GtkApplication *app)
{
    GtkWidget *reminder_win;
    GtkWidget *vbox, *top_box, *left_box, *right_box, *time_box, *scroll, *save_button;
    GtkWidget *calendar, *hour, *minute, *textview;

    reminder_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(reminder_win), "Reminder");
    gtk_window_set_default_size(GTK_WINDOW(reminder_win), 600, 300);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(reminder_win), vbox);

    /* ---------- TOP HORIZONTAL BOX ---------- */
    top_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), top_box, TRUE, TRUE, 5);

    /* ---------- LEFT SIDE (Calendar + Time) ---------- */
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(top_box), left_box, FALSE, FALSE, 5);

    /* Calendar */
    calendar = gtk_calendar_new();
    gtk_widget_set_margin_top(calendar, 5);
    gtk_widget_set_margin_bottom(calendar, 5);
    gtk_box_pack_start(GTK_BOX(left_box), calendar, FALSE, FALSE, 5);

    /* Set default date to today */
    GDateTime *now = g_date_time_new_now_local();
    gtk_calendar_select_month(GTK_CALENDAR(calendar),
                              g_date_time_get_month(now) - 1,
                              g_date_time_get_year(now));
    gtk_calendar_select_day(GTK_CALENDAR(calendar),
                            g_date_time_get_day_of_month(now));

    /* Time selection */
    time_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    hour   = gtk_combo_box_text_new();
    minute = gtk_combo_box_text_new();
    gtk_widget_set_size_request(hour, 80, -1);
    gtk_widget_set_size_request(minute, 80, -1);

    /* Populate hours */
    for (int i = 0; i <= 23; i++) {
        char buf[4];
        sprintf(buf, "%02d", i);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(hour), buf);
    }

    /* Populate minutes */
    for (int i = 0; i <= 59; i++) {
        char buf[4];
        sprintf(buf, "%02d", i);
        gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(minute), buf);
    }

    /* Set default time to current */
    gtk_combo_box_set_active(GTK_COMBO_BOX(hour), g_date_time_get_hour(now));
    gtk_combo_box_set_active(GTK_COMBO_BOX(minute), g_date_time_get_minute(now));

    gtk_box_pack_start(GTK_BOX(time_box), hour, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(time_box), minute, FALSE, FALSE, 5);
    gtk_box_pack_start(GTK_BOX(left_box), time_box, FALSE, FALSE, 5);

    g_date_time_unref(now);

    /* ---------- RIGHT SIDE (Text Input) ---------- */
    right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(top_box), right_box, TRUE, TRUE, 5);

    textview = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(textview), GTK_WRAP_WORD_CHAR);

    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), textview);
    gtk_widget_set_vexpand(scroll, TRUE);
    gtk_widget_set_hexpand(scroll, TRUE);

    gtk_box_pack_start(GTK_BOX(right_box), scroll, TRUE, TRUE, 5);

    /* ---------- SAVE BUTTON ---------- */
    save_button = gtk_button_new_with_label("Save");
    gtk_box_pack_start(GTK_BOX(vbox), save_button, FALSE, FALSE, 5);

    /* ---------- REMINDER WIDGET STRUCT ---------- */
    ReminderWidgets *rw = g_malloc(sizeof(ReminderWidgets));
    rw->year = calendar;
    rw->month = calendar;
    rw->day = calendar;
    rw->hour = hour;
    rw->minute = minute;
    rw->textview = textview;

    /* ---------- Connect save button ---------- */
    g_signal_connect(save_button, "clicked", G_CALLBACK(save_reminder), rw);

    gtk_widget_show_all(reminder_win);
}


/*############################# Reminder End ########################################*/













/*#####################################################################################*/
/* --------------------------------- Timer Window ----------------------------------- */
/*#####################################################################################*/

typedef struct {
    GtkWidget *time_label;
    GtkWidget *lap_list;
    gboolean running;
    guint timer_id;
    guint64 start_time;
    guint64 elapsed_ms;
} Stopwatch;


static gboolean update_time_cb(gpointer data)
{
    Stopwatch *sw = data;

    guint64 now = g_get_monotonic_time() / 1000;
    guint64 total = sw->elapsed_ms + (now - sw->start_time);

    guint ms = total % 1000;
    guint sec = (total / 1000) % 60;
    guint min = (total / 60000) % 60;
    guint hr  = total / 3600000;

    char buf[64];
    snprintf(buf, sizeof(buf),
             "%02u : %02u : %02u . %03u",
             hr, min, sec, ms);

    gtk_label_set_text(GTK_LABEL(sw->time_label), buf);
    return TRUE;
}





static void start_stop_cb(GtkButton *btn, gpointer data)
{
    Stopwatch *sw = data;
    GtkStyleContext *ctx = gtk_widget_get_style_context(GTK_WIDGET(btn));

    if (!sw->running) {
        sw->running = TRUE;
        sw->start_time = g_get_monotonic_time() / 1000;
        sw->timer_id = g_timeout_add(10, update_time_cb, sw);

        gtk_button_set_label(btn, "Stop");
        gtk_style_context_remove_class(ctx, "start");
        gtk_style_context_add_class(ctx, "stop");
    } else {
        sw->running = FALSE;
        g_source_remove(sw->timer_id);

        guint64 now = g_get_monotonic_time() / 1000;
        sw->elapsed_ms += (now - sw->start_time);

        gtk_button_set_label(btn, "Start");
        gtk_style_context_remove_class(ctx, "stop");
        gtk_style_context_add_class(ctx, "start");
    }
}



static void reset_cb(GtkButton *btn, gpointer data)
{
    Stopwatch *sw = data;

    if (sw->running) {
        g_source_remove(sw->timer_id);
        sw->running = FALSE;
    }

    sw->elapsed_ms = 0;
    gtk_label_set_text(GTK_LABEL(sw->time_label),
                       "00 : 00 : 00 . 000");
}



static void lap_cb(GtkButton *btn, gpointer data)
{
    Stopwatch *sw = data;

    const char *t = gtk_label_get_text(GTK_LABEL(sw->time_label));
    GtkWidget *label = gtk_label_new(t);
    gtk_box_pack_start(GTK_BOX(sw->lap_list), label, FALSE, FALSE, 2);
    gtk_widget_show(label);
}


static void load_stopwatch_css(void)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(provider,
        ".circle-btn {"
        "  border-radius: 50%;"
        "  font-size: 16px;"
        "  font-weight: bold;"
        "}"
        ".start { background:rgb(0, 133, 55); color: white; }"
        ".stop  { background: #e74c3c; color: white; }"
        ".center-dark { background:rgb(27, 27, 27); }"
        , -1, NULL);

    gtk_style_context_add_provider_for_screen(
        gdk_screen_get_default(),
        GTK_STYLE_PROVIDER(provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);

    g_object_unref(provider);
}



static void create_timer_win(GtkApplication *app)
{
    load_stopwatch_css();

    GtkWidget *win, *main_box;
    GtkWidget *left_box, *center_box, *right_box;
    GtkWidget *start_btn, *reset_btn, *lap_btn;
    GtkWidget *time_label, *scroll, *lap_box, *btn_row;

    Stopwatch *sw = g_malloc0(sizeof(Stopwatch));

    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Stopwatch");
    gtk_window_set_default_size(GTK_WINDOW(win), 300, 120);

    main_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    gtk_container_add(GTK_CONTAINER(win), main_box);

    /* LEFT */
    left_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 15);
    gtk_box_pack_start(GTK_BOX(main_box), left_box, FALSE, FALSE, 10);

    start_btn = gtk_button_new_with_label("Start");
    gtk_widget_set_size_request(start_btn, 90, 90);
    gtk_style_context_add_class(
        gtk_widget_get_style_context(start_btn), "circle-btn");
    gtk_style_context_add_class(
        gtk_widget_get_style_context(start_btn), "start");

    gtk_box_pack_start(GTK_BOX(left_box), start_btn, FALSE, FALSE, 5);

    btn_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    reset_btn = gtk_button_new_with_label("Restart");
    lap_btn   = gtk_button_new_with_label("Lap");

    gtk_box_pack_start(GTK_BOX(btn_row), reset_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(btn_row), lap_btn, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(left_box), btn_row, FALSE, FALSE, 5);

    /* CENTER */
    center_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(main_box), center_box, TRUE, TRUE, 0);
    gtk_style_context_add_class(
        gtk_widget_get_style_context(center_box), "center-dark");

    time_label = gtk_label_new("00 : 00 : 00 . 000");
    gtk_widget_set_halign(time_label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(time_label, GTK_ALIGN_CENTER);

    PangoAttrList *attrs = pango_attr_list_new();
    pango_attr_list_insert(attrs, pango_attr_scale_new(2.7));
    pango_attr_list_insert(attrs,
        pango_attr_foreground_new(65535, 65535, 65535));
    gtk_label_set_attributes(GTK_LABEL(time_label), attrs);
    pango_attr_list_unref(attrs);

    gtk_box_pack_start(GTK_BOX(center_box), time_label, TRUE, TRUE, 0);

    /* RIGHT */
    right_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(main_box), right_box, FALSE, FALSE, 10);
    gtk_widget_set_margin_top(right_box, 10);
    gtk_widget_set_margin_bottom(right_box, 10);

    lap_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_widget_set_size_request(scroll, 180, -1);
    gtk_container_add(GTK_CONTAINER(scroll), lap_box);
    gtk_box_pack_start(GTK_BOX(right_box), scroll, TRUE, TRUE, 0);

    /* STORE */
    sw->time_label = time_label;
    sw->lap_list = lap_box;

    /* SIGNALS */
    g_signal_connect(start_btn, "clicked", G_CALLBACK(start_stop_cb), sw);
    g_signal_connect(reset_btn, "clicked", G_CALLBACK(reset_cb), sw);
    g_signal_connect(lap_btn, "clicked", G_CALLBACK(lap_cb), sw);

    gtk_widget_show_all(win);
}




/*#########################################  Timer End  ################################################*/


/*######################################################################################################*/
/* ---------------------------------------- Converter Window ------------------------------------------ */
/*######################################################################################################*/



float convert_value(int choice, float value, const char **unit)
{
    float result = 0.0f;

    switch (choice) {
        case 1:  result = value * 100;        *unit = "Centimeter"; break;
        case 2:  result = value / 100;        *unit = "Meter"; break;
        case 3:  result = (value * 9 / 5) + 32; *unit = "Fahrenheit"; break;
        case 4:  result = (value - 32) * 5 / 9; *unit = "Celsius"; break;
        case 5:  result = value * 1000;       *unit = "Gram"; break;
        case 6:  result = value / 1000;       *unit = "Kilogram"; break;
        case 7:  result = value * 60;         *unit = "Minute"; break;
        case 8:  result = value / 60;         *unit = "Hour"; break;
        case 9:  result = value * 1000 / 3600; *unit = "m/sec"; break;
        case 10: result = value * 3600 / 1000; *unit = "Km/hr"; break;
        default: *unit = "Invalid";
    }

    return result;
}




    typedef struct {
        GtkWidget *combo;
        GtkWidget *input;
        GtkWidget *output;
    } ConverterWidgets;

    static void on_convert_clicked(GtkButton *button, gpointer data)
    {
        ConverterWidgets *w = data;

        int choice = gtk_combo_box_get_active(GTK_COMBO_BOX(w->combo)) + 1;
        const char *text = gtk_entry_get_text(GTK_ENTRY(w->input));

        if (choice <= 0 || text[0] == '\0') {
            gtk_entry_set_text(GTK_ENTRY(w->output), "Invalid Input");
            return;
        }

        float value = atof(text);
        const char *unit;
        float result = convert_value(choice, value, &unit);

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%.2f %s", result, unit);
        gtk_entry_set_text(GTK_ENTRY(w->output), buffer);
    }


    static int swap_choice(int choice)
    {
        if (choice % 2 == 0)
            return choice - 1;
        else
            return choice + 1;
    }

    static void auto_convert(ConverterWidgets *w)
    {
        const char *text = gtk_entry_get_text(GTK_ENTRY(w->input));
        int choice = gtk_combo_box_get_active(GTK_COMBO_BOX(w->combo)) + 1;

        if (text[0] == '\0' || choice <= 0) {
            gtk_entry_set_text(GTK_ENTRY(w->output), "");
            return;
        }

        float value = atof(text);
        const char *unit;

        float result = convert_value(choice, value, &unit);

        char buffer[64];
        snprintf(buffer, sizeof(buffer), "%.2f %s", result, unit);
        gtk_entry_set_text(GTK_ENTRY(w->output), buffer);
    }

    static void on_input_changed(GtkEditable *editable, gpointer data)
    {
            auto_convert((ConverterWidgets *)data);
    }

    static void on_combo_changed(GtkComboBox *box, gpointer data)
    {
            auto_convert((ConverterWidgets *)data);
    }


    static void on_swap_clicked(GtkButton *button, gpointer data)
    {
            ConverterWidgets *w = data;

            int current = gtk_combo_box_get_active(GTK_COMBO_BOX(w->combo)) + 1;
            int swapped = swap_choice(current) - 1;

            gtk_combo_box_set_active(GTK_COMBO_BOX(w->combo), swapped);
            auto_convert(w);
    }







static void create_converter_win(GtkApplication *app)
{
    GtkWidget *converter_win;
    GtkWidget *vbox, *hbox;
    GtkWidget *combo, *input, *output, *swap_btn;

    ConverterWidgets *widgets = g_malloc(sizeof(ConverterWidgets));

    converter_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(converter_win), "Unit Converter");
    gtk_window_set_default_size(GTK_WINDOW(converter_win), 600, 200);
    gtk_container_set_border_width(GTK_CONTAINER(converter_win), 15);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(converter_win), vbox);

    /* -------- Dropdown -------- */
    combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Meter → Centimeter");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Centimeter → Meter");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Celsius → Fahrenheit");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Fahrenheit → Celsius");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Kilogram → Gram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Gram → Kilogram");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Hour → Minute");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Minute → Hour");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "Km/hr → m/sec");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo), "m/sec → Km/hr");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);

    gtk_box_pack_start(GTK_BOX(vbox), combo, FALSE, FALSE, 0);

    /* -------- Input / Swap / Output -------- */
    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    input = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(input), "Enter value");

    swap_btn = gtk_button_new_with_label("<< ==== >>");

    output = gtk_entry_new();
    gtk_widget_set_sensitive(output, FALSE);

    gtk_box_pack_start(GTK_BOX(hbox), input, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), swap_btn, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(hbox), output, TRUE, TRUE, 0);

    widgets->combo = combo;
    widgets->input = input;
    widgets->output = output;

    /* -------- Signals -------- */
    g_signal_connect(input, "changed",
                     G_CALLBACK(on_input_changed), widgets);

    g_signal_connect(combo, "changed",
                     G_CALLBACK(on_combo_changed), widgets);

    g_signal_connect(swap_btn, "clicked",
                     G_CALLBACK(on_swap_clicked), widgets);

    gtk_widget_show_all(converter_win);
}


/*######################################### Converter End ################################################*/






/*###############################################################################*/
/* ------------------------------ Apps Window ------------------------------ */
/*##############################################################################*/


/* ---------- Callbacks ---------- */
static void open_vscode(GtkWidget *widget, gpointer data)
{
    system("code &");
}

static void open_calculator(GtkWidget *widget, gpointer data)
{
    system("gnome-calculator &");
}

static void open_calendar(GtkWidget *w, gpointer d) {
    system("gnome-calendar &");
}

static void open_contacts(GtkWidget *w, gpointer d) {
    system("gnome-contacts &");
}

static void open_files(GtkWidget *w, gpointer d) {
    system("nautilus &");
}

static void open_firefox(GtkWidget *w, gpointer d) {
    system("firefox &");
}

static void open_geary(GtkWidget *w, gpointer d) {
    system("geary &");
}

/* LibreOffice */
static void open_libreoffice(GtkWidget *w, gpointer d) {
    system("libreoffice &");
}

static void open_writer(GtkWidget *w, gpointer d) {
    system("libreoffice --writer &");
}

static void open_calc(GtkWidget *w, gpointer d) {
    system("libreoffice --calc &");
}

static void open_draw(GtkWidget *w, gpointer d) {
    system("libreoffice --draw &");
}

static void open_impress(GtkWidget *w, gpointer d) {
    system("libreoffice --impress &");
}

static void open_math(GtkWidget *w, gpointer d) {
    system("libreoffice --math &");
}





/* ---------- Helper to create app button ---------- */
static GtkWidget* create_app_button(
    const char *icon_path,
    const char *label_text,
    GCallback callback
) {
    GtkWidget *button;
    GtkWidget *vbox;
    GtkWidget *image;
    GtkWidget *label;

    button = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(button), GTK_RELIEF_NONE);

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);

    image = gtk_image_new_from_file(icon_path);
    label = gtk_label_new(label_text);

    gtk_box_pack_start(GTK_BOX(vbox), image, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(button), vbox);

    g_signal_connect(button, "clicked", callback, NULL);

    return button;
}

/* ---------- Apps Window ---------- */
static void create_apps_win(GtkApplication *app)
{
    GtkWidget *apps_win;
    GtkWidget *grid;

    apps_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(apps_win), "Apps");
    gtk_window_set_default_size(GTK_WINDOW(apps_win), 300, 300);
    gtk_container_set_border_width(GTK_CONTAINER(apps_win), 15);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 20);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 20);

    GtkWidget *scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(
        GTK_SCROLLED_WINDOW(scroll),
        GTK_POLICY_NEVER,
        GTK_POLICY_AUTOMATIC
    );

    gtk_container_add(GTK_CONTAINER(scroll), grid);
    gtk_container_add(GTK_CONTAINER(apps_win), scroll);




    /* ---------- App Buttons ---------- */
    GtkWidget *btn_calc = create_app_button(
        "src/img/calculator.png",
        "Calculator",
        G_CALLBACK(open_calculator)
    );

    GtkWidget *btn_code = create_app_button(
        "src/img/code.png",   // add this icon
        "VS Code",
        G_CALLBACK(open_vscode)
    );
    GtkWidget *btn_calendar = create_app_button(
    "src/img/calendar.png",
    "Calendar",
    G_CALLBACK(open_calendar)
    );

    GtkWidget *btn_contacts = create_app_button(
        "src/img/contacts.png",
        "Contacts",
        G_CALLBACK(open_contacts)
    );

    GtkWidget *btn_files = create_app_button(
        "src/img/files.png",
        "Files",
        G_CALLBACK(open_files)
    );

    GtkWidget *btn_firefox = create_app_button(
        "src/img/firefox.png",
        "Firefox",
        G_CALLBACK(open_firefox)
    );

    GtkWidget *btn_geary = create_app_button(
        "src/img/geary.png",
        "Geary",
        G_CALLBACK(open_geary)
    );

    /* LibreOffice */
    GtkWidget *btn_lo = create_app_button(
        "src/img/libreoffice.png",
        "LibreOffice",
        G_CALLBACK(open_libreoffice)
    );

    GtkWidget *btn_writer = create_app_button(
        "src/img/writer.png",
        "Writer",
        G_CALLBACK(open_writer)
    );

    GtkWidget *btn_lcalc = create_app_button(
        "src/img/calc.png",
        "Calc",
        G_CALLBACK(open_calc)
    );

    GtkWidget *btn_draw = create_app_button(
        "src/img/draw.png",
        "Draw",
        G_CALLBACK(open_draw)
    );

    GtkWidget *btn_impress = create_app_button(
        "src/img/impress.png",
        "Impress",
        G_CALLBACK(open_impress)
    );

    GtkWidget *btn_math = create_app_button(
        "src/img/math.png",
        "Math",
        G_CALLBACK(open_math)
    );


    /* ---------- Place in grid ---------- */
    gtk_grid_attach(GTK_GRID(grid), btn_calc,     0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_code,     1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_calendar, 2, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_contacts, 3, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_files,    0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_firefox,  1, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_geary,    2, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_lo,       3, 1, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_writer,   0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_lcalc,    1, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_draw,     2, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), btn_impress,  3, 2, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), btn_math,     0, 3, 1, 1);






    gtk_widget_show_all(apps_win);
}



/*######################################### Apps End ################################################*/









/*##################################################################################################*/
/* -------------------------------------- Notes Window -------------------------------------------- */
/*##################################################################################################*/
/* ===================== DATA STRUCT ===================== */

typedef struct {
    GtkWidget *list_box;
    GtkWidget *title_entry;
    GtkWidget *content_view;
    GtkWidget *preview_win;
} NotesWidgets;

/* ===================== FORWARD DECLARATIONS ===================== */

static void load_notes(NotesWidgets *w);
static void show_note_content(const char *title, GtkTextBuffer *buffer);
static GtkWidget *create_note_row(const char *title, NotesWidgets *w);
static void on_save_clicked(GtkButton *btn, gpointer data);
static void delete_note(const char *title, NotesWidgets *w);

/* ===================== HOVER HANDLER ===================== */

static void show_preview_window(const char *title,
                                int x, int y,
                                NotesWidgets *w)
{
    GtkWidget *scroll, *text;
    GtkTextBuffer *buffer;

    // Destroy existing preview window if it exists
    if (w->preview_win) {
        gtk_widget_destroy(w->preview_win);
        w->preview_win = NULL;
    }

    // Create new preview window
    w->preview_win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_type_hint(GTK_WINDOW(w->preview_win), GDK_WINDOW_TYPE_HINT_TOOLTIP);
    gtk_window_set_decorated(GTK_WINDOW(w->preview_win), FALSE);
    gtk_window_set_default_size(GTK_WINDOW(w->preview_win), 300, 200);
    gtk_window_set_resizable(GTK_WINDOW(w->preview_win), TRUE);
    gtk_window_move(GTK_WINDOW(w->preview_win), x + 15, y + 15);
    
    // Set transient for main window so it stays on top
    GtkWidget *main_win = gtk_widget_get_ancestor(w->list_box, GTK_TYPE_WINDOW);
    if (main_win) {
        gtk_window_set_transient_for(GTK_WINDOW(w->preview_win), GTK_WINDOW(main_win));
    }

    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(w->preview_win), scroll);

    text = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text), GTK_WRAP_WORD_CHAR);
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(text), FALSE);
    gtk_container_add(GTK_CONTAINER(scroll), text);

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text));
    show_note_content(title, buffer);

    gtk_widget_show_all(w->preview_win);
}

static gboolean on_row_leave(GtkWidget *widget,
                             GdkEventCrossing *event,
                             gpointer data)
{
    NotesWidgets *w = data;

    // Add a small delay to prevent flickering when moving between rows
    g_timeout_add(100, (GSourceFunc)gtk_widget_destroy, w->preview_win);
    w->preview_win = NULL;
    
    return FALSE;
}

static gboolean on_row_enter(GtkWidget *widget,
                             GdkEventCrossing *event,
                             gpointer data)
{
    NotesWidgets *w = data;
    const char *title = gtk_widget_get_name(widget);

    show_preview_window(title,
                        event->x_root,
                        event->y_root,
                        w);
    return FALSE;
}

static gboolean on_title_clicked(GtkWidget *widget,
                                 GdkEventButton *event,
                                 gpointer data)
{
    NotesWidgets *w = data;
    const char *title = gtk_widget_get_name(widget);

    // Destroy preview window when clicking a note
    if (w->preview_win) {
        gtk_widget_destroy(w->preview_win);
        w->preview_win = NULL;
    }

    GtkTextBuffer *buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(w->content_view));
    
    // Update the title entry with the clicked note's title
    gtk_entry_set_text(GTK_ENTRY(w->title_entry), title);
    
    show_note_content(title, buffer);

    return TRUE;
}

/* ===================== CREATE TITLE ROW ===================== */

static GtkWidget *create_note_row(const char *title, NotesWidgets *w)
{
    GtkWidget *event_box = gtk_event_box_new();
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
    GtkWidget *label = gtk_label_new(title);
    GtkWidget *del = gtk_button_new_with_label("✕");

    // Set name for event box
    gtk_widget_set_name(event_box, title);

    // Wrap long titles
    gtk_label_set_line_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_max_width_chars(GTK_LABEL(label), 20);
    gtk_label_set_xalign(GTK_LABEL(label), 0.0);

    // Padding
    gtk_widget_set_margin_start(box, 5);
    gtk_widget_set_margin_end(box, 5);
    gtk_widget_set_margin_top(box, 5);
    gtk_widget_set_margin_bottom(box, 5);

    /* Connect delete button - FIXED VERSION */
    // Create a copy of the title for the callback
    char *title_copy = g_strdup(title);

  g_signal_connect_swapped(del, "clicked",
                             G_CALLBACK(delete_note), g_strdup(title));
    
    // Store the title in the button's data
    g_object_set_data_full(G_OBJECT(del), "note-title", 
                          title_copy, (GDestroyNotify)g_free);

    // Pack label and delete button
    gtk_box_pack_start(GTK_BOX(box), label, TRUE, TRUE, 0);
    gtk_box_pack_end(GTK_BOX(box), del, FALSE, FALSE, 0);
    
    // Add box to event box
    gtk_container_add(GTK_CONTAINER(event_box), box);

    // Connect hover and click signals
    g_signal_connect(event_box, "button-press-event",
                     G_CALLBACK(on_title_clicked), w);
    g_signal_connect(event_box, "enter-notify-event",
                     G_CALLBACK(on_row_enter), w);
    g_signal_connect(event_box, "leave-notify-event",
                     G_CALLBACK(on_row_leave), w);

    // Enable events
    gtk_widget_set_events(event_box, 
                         GDK_BUTTON_PRESS_MASK | 
                         GDK_ENTER_NOTIFY_MASK | 
                         GDK_LEAVE_NOTIFY_MASK);

    return event_box;
}
/* ===================== LOAD NOTES ===================== */

static void load_notes(NotesWidgets *w)
{
    // Clear existing notes
    GList *children, *iter;
    children = gtk_container_get_children(GTK_CONTAINER(w->list_box));
    for (iter = children; iter != NULL; iter = g_list_next(iter)) {
        gtk_widget_destroy(GTK_WIDGET(iter->data));
    }
    g_list_free(children);

    FILE *fp = fopen("notes.txt", "r");
    if (!fp) return;

    char line[256], title[128];
    int in_note = 0;

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0; // Remove newline
        
        if (line[0] == '(') {
            sscanf(line, "(%[^)])", title);
            GtkWidget *row = create_note_row(title, w);
            gtk_box_pack_start(GTK_BOX(w->list_box), row, FALSE, FALSE, 0);
            in_note = 1;
        } else if (line[0] == '}') {
            in_note = 0;
        }
    }

    fclose(fp);
    gtk_widget_show_all(w->list_box);
}

/* ===================== SHOW CONTENT ===================== */

static void show_note_content(const char *title, GtkTextBuffer *buffer)
{
    FILE *fp = fopen("notes.txt", "r");
    if (!fp) {
        gtk_text_buffer_set_text(buffer, "Note not found", -1);
        return;
    }

    char line[256], t[128];
    gboolean match = FALSE;
    GString *content = g_string_new("");

    while (fgets(line, sizeof(line), fp)) {
        line[strcspn(line, "\n")] = 0;
        
        if (line[0] == '(') {
            sscanf(line, "(%[^)])", t);
            match = (strcmp(t, title) == 0);
            continue;
        }
        if (match && line[0] == '}') break;
        if (match && strlen(line) > 0) {
            g_string_append_printf(content, "%s\n", line);
        }
    }

    fclose(fp);
    
    if (content->len > 0) {
        gtk_text_buffer_set_text(buffer, content->str, -1);
    } else {
        gtk_text_buffer_set_text(buffer, "Note content is empty", -1);
    }
    
    g_string_free(content, TRUE);
}

/* ===================== SAVE NOTE ===================== */

static void on_save_clicked(GtkButton *btn, gpointer data)
{
    NotesWidgets *w = data;

    const char *title = gtk_entry_get_text(GTK_ENTRY(w->title_entry));

    if (strlen(title) == 0) {
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
            GTK_DIALOG_MODAL,
            GTK_MESSAGE_WARNING,
            GTK_BUTTONS_OK,
            "Please enter a title");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
        return;
    }

    GtkTextBuffer *buf = gtk_text_view_get_buffer(GTK_TEXT_VIEW(w->content_view));
    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buf, &start, &end);
    char *content = gtk_text_buffer_get_text(buf, &start, &end, FALSE);

    // Check if note already exists
    gboolean note_exists = FALSE;
    FILE *check_fp = fopen("notes.txt", "r");
    if (check_fp) {
        char line[256], t[128];
        while (fgets(line, sizeof(line), check_fp)) {
            if (line[0] == '(') {
                sscanf(line, "(%[^)])", t);
                if (strcmp(t, title) == 0) {
                    note_exists = TRUE;
                    break;
                }
            }
        }
        fclose(check_fp);
    }

    if (note_exists) {
        // Update existing note
        FILE *fp = fopen("notes.txt", "r");
        FILE *tmp = fopen("tmp.txt", "w");
        
        if (fp && tmp) {
            char line[256], t[128];
            gboolean in_note = FALSE;
            
            while (fgets(line, sizeof(line), fp)) {
                if (line[0] == '(') {
                    sscanf(line, "(%[^)])", t);
                    in_note = (strcmp(t, title) == 0);
                }
                
                if (!in_note) {
                    fputs(line, tmp);
                } else if (line[0] == '}') {
                    fprintf(tmp, "(%s){\n%s\n}\n\n", title, content);
                    in_note = FALSE;
                }
            }
            
            fclose(fp);
            fclose(tmp);
            rename("tmp.txt", "notes.txt");
        }
    } else {
        // Append new note
        FILE *fp = fopen("notes.txt", "a");
        if (fp) {
            fprintf(fp, "(%s){\n%s\n}\n\n", title, content);
            fclose(fp);
            
            GtkWidget *row = create_note_row(title, w);
            gtk_box_pack_start(GTK_BOX(w->list_box), row, FALSE, FALSE, 0);
            gtk_widget_show_all(w->list_box);
        }
    }

    // Clear input fields
    gtk_entry_set_text(GTK_ENTRY(w->title_entry), "");
    gtk_text_buffer_set_text(buf, "", -1);
    g_free(content);
}

\
/* ===================== DELETE NOTE ===================== */

static void delete_note(const char *title, NotesWidgets *w)
{
    FILE *fp = fopen("notes.txt", "r");
    FILE *tmp = fopen("tmp.txt", "w");

    char line[256], t[128];
    gboolean skip = FALSE;

    while (fgets(line, sizeof(line), fp)) {
        if (line[0] == '(') {
            sscanf(line, "(%[^)])", t);
            skip = strcmp(t, title) == 0;
        }
        if (!skip) fputs(line, tmp);
        if (skip && line[0] == '}') skip = FALSE;
    }

    fclose(fp);
    fclose(tmp);
    rename("tmp.txt", "notes.txt");
    load_notes(w);
}

/* ===================== MAIN NOTES WINDOW ===================== */

static void create_notes_win(GtkApplication *app)
{
    GtkWidget *win, *hbox, *left, *right;
    GtkWidget *title, *content, *save, *scroll;

    NotesWidgets *w = g_malloc0(sizeof(NotesWidgets));

    win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(win), "Notes");
    gtk_window_set_default_size(GTK_WINDOW(win), 900, 500);
    gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);
    gtk_container_add(GTK_CONTAINER(win), hbox);

    /* ---------- LEFT PANEL ---------- */
    left = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_widget_set_size_request(left, 250, -1);
    gtk_box_pack_start(GTK_BOX(hbox), left, FALSE, FALSE, 0);

    // Add a frame and scroll window for the notes list
    GtkWidget *frame = gtk_frame_new(NULL);
    gtk_box_pack_start(GTK_BOX(left), frame, TRUE, TRUE, 0);
    
    GtkWidget *scroll_left = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll_left),
                                   GTK_POLICY_NEVER,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(frame), scroll_left);
    
    w->list_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
    gtk_container_add(GTK_CONTAINER(scroll_left), w->list_box);

    /* ---------- RIGHT PANEL ---------- */
    right = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(hbox), right, TRUE, TRUE, 0);

    title = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(title), "Title");
    gtk_widget_set_margin_top(title, 5);
    gtk_widget_set_margin_bottom(title, 5);
    gtk_widget_set_margin_start(title, 5);
    gtk_widget_set_margin_end(title, 5);

    content = gtk_text_view_new();
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(content), GTK_WRAP_WORD_CHAR);
    
    // Add margin to text view
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(content), 10);
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(content), 10);
    gtk_text_view_set_top_margin(GTK_TEXT_VIEW(content), 10);
    gtk_text_view_set_bottom_margin(GTK_TEXT_VIEW(content), 10);

    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scroll),
                                   GTK_POLICY_AUTOMATIC,
                                   GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scroll), content);
    gtk_widget_set_margin_top(scroll, 5);
    gtk_widget_set_margin_bottom(scroll, 5);
    gtk_widget_set_margin_start(scroll, 5);
    gtk_widget_set_margin_end(scroll, 5);

    save = gtk_button_new_with_label("Save");
    gtk_widget_set_margin_start(save, 5);
    gtk_widget_set_margin_end(save, 5);
    gtk_widget_set_margin_bottom(save, 5);

    gtk_box_pack_start(GTK_BOX(right), title, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(right), scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(right), save, FALSE, FALSE, 0);

    w->title_entry = title;
    w->content_view = content;
    w->preview_win = NULL;

    load_notes(w);

    g_signal_connect(save, "clicked",
                     G_CALLBACK(on_save_clicked), w);
    
   

    gtk_widget_show_all(win);
}


/*###################################### Notes End ##################################################*/





/*####################################################################################################*/
/* --------------------------------------- SMS Window ----------------------------------------------- */
/*####################################################################################################*/

typedef struct {
    char *msg;
    gboolean is_self;
} UiMsg;




#define BUF_SIZE 512

extern int start_chat();
extern int send_message(const char *msg);
extern int receive_message(char *buffer);

static GtkWidget *text_view;
static GtkTextBuffer *text_buffer;
static GtkWidget *entry;
static GtkTextTag *tag_left;
static GtkTextTag *tag_right;


static void append_message(const char *msg, gboolean is_self)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(text_buffer, &end);

    if (is_self) {
        gtk_text_buffer_insert_with_tags(
            text_buffer, &end, msg, -1, tag_right, NULL);
    } else {
        gtk_text_buffer_insert_with_tags(
            text_buffer, &end, msg, -1, tag_left, NULL);
    }

    gtk_text_buffer_insert(text_buffer, &end, "\n\n", -1);
}


static void on_send_clicked(GtkButton *button, gpointer data)
{
    const char *msg = gtk_entry_get_text(GTK_ENTRY(entry));
    if (strlen(msg) == 0) return;

    send_message(msg);
    append_message(msg, TRUE);
    gtk_entry_set_text(GTK_ENTRY(entry), "");
}

static gboolean ui_append_cb(gpointer data)
{
    UiMsg *m = data;
    append_message(m->msg, m->is_self);
    g_free(m->msg);
    g_free(m);
    return FALSE;   // run once
}


static gpointer receive_thread(gpointer data)
{
    char buffer[BUF_SIZE];

    while (1) {
        int n = receive_message(buffer);
        if (n <= 0)
            break;

        UiMsg *m = g_malloc(sizeof(UiMsg));
        m->msg = g_strdup(buffer);
        m->is_self = FALSE;

        g_idle_add(ui_append_cb, m);
    }
    return NULL;
}


static gpointer start_chat_thread(gpointer data)
{
    start_chat();          // blocking accept()
    g_thread_new("recv", receive_thread, NULL);
    return NULL;
}



static void create_sms_start_win(GtkApplication *app)
{
    GtkWidget *sms_win;
    GtkWidget *vbox, *hbox;
    GtkWidget *scroll;
    GtkWidget *send_btn;

    sms_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(sms_win), "SMS");
    gtk_window_set_default_size(GTK_WINDOW(sms_win), 500, 300);

    /* -------- Window Margin -------- */
    gtk_container_set_border_width(GTK_CONTAINER(sms_win), 10); // ← margin

    vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 8);
    gtk_container_add(GTK_CONTAINER(sms_win), vbox);

    text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(text_view), FALSE);
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD_CHAR);

    /* -------- Text Padding -------- */
    gtk_text_view_set_left_margin(GTK_TEXT_VIEW(text_view), 10);  // padding
    gtk_text_view_set_right_margin(GTK_TEXT_VIEW(text_view), 10); // padding

    text_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    /* -------- Text Alignment Tags -------- */
    tag_left = gtk_text_buffer_create_tag(
        text_buffer, "left",
        "justification", GTK_JUSTIFY_LEFT,
        NULL);

    tag_right = gtk_text_buffer_create_tag(
        text_buffer, "right",
        "justification", GTK_JUSTIFY_RIGHT,
        NULL);

    scroll = gtk_scrolled_window_new(NULL, NULL);

    /* -------- Scroll Padding -------- */
    gtk_container_set_border_width(GTK_CONTAINER(scroll), 5); // padding

    gtk_container_add(GTK_CONTAINER(scroll), text_view);
    gtk_box_pack_start(GTK_BOX(vbox), scroll, TRUE, TRUE, 0);

    hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

    /* -------- Bottom Box Margin -------- */
    gtk_container_set_border_width(GTK_CONTAINER(hbox), 5); // margin

    gtk_box_pack_start(GTK_BOX(vbox), hbox, FALSE, FALSE, 0);

    entry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(hbox), entry, TRUE, TRUE, 0);

    send_btn = gtk_button_new_with_label("Send");
    gtk_box_pack_start(GTK_BOX(hbox), send_btn, FALSE, FALSE, 0);

    g_signal_connect(send_btn, "clicked",
                     G_CALLBACK(on_send_clicked), NULL);

    gtk_widget_show_all(sms_win);

    g_thread_new("chat", start_chat_thread, NULL);
}


/*############################################## SMS End ###############################################*/








/* ---------------- Sent Window ---------------- */

static void create_sent_win(GtkApplication *app)
{
    GtkWidget *sent_win;
    GtkWidget *label;

    sent_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(sent_win), "Sent");
    gtk_window_set_default_size(GTK_WINDOW(sent_win), 500, 200);

    label = gtk_label_new("This is the Sent window");
    gtk_container_add(GTK_CONTAINER(sent_win), label);

    gtk_widget_show_all(sent_win);
}

/* ---------------- Setting Window ---------------- */

/* ---------- System Control Functions ---------- */

static void toggle_wifi(GtkButton *button, gpointer user_data)
{
    system("nmcli radio wifi | grep -q enabled && nmcli radio wifi off || nmcli radio wifi on");
}


static void toggle_bluetooth(GtkButton *button, gpointer user_data)
{
    system("rfkill list bluetooth | grep -q 'Soft blocked: yes' && rfkill unblock bluetooth || rfkill block bluetooth");
}

static void toggle_mute(GtkButton *button, gpointer user_data)
{
    system("amixer set Master toggle");
}

static void set_volume(GtkRange *range, gpointer user_data)
{
    int volume = (int)gtk_range_get_value(range);
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "amixer set Master %d%%", volume);
    system(cmd);
}

static void set_brightness(GtkRange *range, gpointer user_data)
{
    int brightness = (int)gtk_range_get_value(range);
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "xbacklight -set %d", brightness);
    system(cmd);
}

/* ---------- Setting Window ---------- */

static void create_setting_win(GtkApplication *app)
{
    GtkWidget *setting_win;
    GtkWidget *grid;

    GtkWidget *wifi_btn;
    GtkWidget *bt_btn;
    GtkWidget *mute_btn;
    GtkWidget *vol_slider;
    GtkWidget *bright_slider;

    setting_win = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(setting_win), "Settings");
    gtk_window_set_default_size(GTK_WINDOW(setting_win), 500, 250);
    gtk_container_set_border_width(GTK_CONTAINER(setting_win), 15);

    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 10);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 15);
    gtk_container_add(GTK_CONTAINER(setting_win), grid);

    /* Buttons */
    wifi_btn = gtk_button_new_with_label("WiFi ON / OFF");
    bt_btn   = gtk_button_new_with_label("Bluetooth ON / OFF");
    mute_btn = gtk_button_new_with_label("Mute / Unmute");

    /* Sliders */
    vol_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 0, 100, 1);
    gtk_scale_set_value_pos(GTK_SCALE(vol_slider), GTK_POS_RIGHT);
    gtk_range_set_value(GTK_RANGE(vol_slider), 50);

    bright_slider = gtk_scale_new_with_range(GTK_ORIENTATION_HORIZONTAL, 1, 100, 1);
    gtk_scale_set_value_pos(GTK_SCALE(bright_slider), GTK_POS_RIGHT);
    gtk_range_set_value(GTK_RANGE(bright_slider), 50);

    /* Attach widgets */
    gtk_grid_attach(GTK_GRID(grid), wifi_btn,      0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), bt_btn,        1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), mute_btn,      2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Volume"),     0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), vol_slider,                 1, 1, 2, 1);

    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Brightness"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), bright_slider,              1, 2, 2, 1);

    /* Signals */
    g_signal_connect(wifi_btn, "clicked", G_CALLBACK(toggle_wifi), NULL);
    g_signal_connect(bt_btn,   "clicked", G_CALLBACK(toggle_bluetooth), NULL);
    g_signal_connect(mute_btn, "clicked", G_CALLBACK(toggle_mute), NULL);
    g_signal_connect(vol_slider, "value-changed", G_CALLBACK(set_volume), NULL);
    g_signal_connect(bright_slider, "value-changed", G_CALLBACK(set_brightness), NULL);

    gtk_widget_show_all(setting_win);
}

/* ---------------- Button Callbacks ---------------- */

static void system_info(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_system_win(app);
    // sysinfo();
}

static void reminder(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_reminder_win(app);
}

static void timer(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_timer_win(app);
}

static void converter(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_converter_win(app);
    // convard();
}

static void apps(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_apps_win(app);
}

static void notes(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_notes_win(app);
}

static void cmd(GtkWidget *widget, gpointer data)
{
    openTerminal();
}

static void sms_start(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_sms_start_win(app);
}

static void sms_join(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_sent_win(app);
}



static void sent(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_sent_win(app);
}

static void setting(GtkWidget *widget, gpointer data)
{
    GtkApplication *app = GTK_APPLICATION(data);
    create_setting_win(app);
}

/* =========================      Main Window     ============================= */

/* Global widgets */
static GtkWidget *chat_text_view;
static GtkTextBuffer *chat_text_buffer;

/* Global widgets */
static GtkWidget *chat_text_view;
static GtkTextBuffer *chat_text_buffer;
static GtkWidget *chat_entry;
static GtkWidget *chat_gif;





char *filter_ai_response(const char *s)
{
    char *out = malloc(strlen(s) + 1);
    int i = 0, j = 0;
    int last_space = 1;

    while (s[i]) {

        /* REMOVE newlines completely */
        if (s[i] == '\n' || s[i] == '\r') {
            i++;
            continue;
        }

        /* REMOVE markdown asterisks */
        if (s[i] == '*') {
            i++;
            continue;
        }

        /* Normalize all whitespace to single space */
        if (isspace((unsigned char)s[i])) {
            if (!last_space) {
                out[j++] = ' ';
                last_space = 1;
            }
            i++;
            continue;
        }

        /* Remove space before punctuation */
        if (strchr(".,!?;:", s[i]) && j > 0 && out[j-1] == ' ')
            j--;

        /* Fix contractions: ' m → 'm */
        if (s[i] == '\'' && s[i+1] == ' ') {
            out[j++] = '\'';
            i += 2;
            last_space = 0;
            continue;
        }

        /* Fix hyphen spacing: note -taking → note-taking */
        if (s[i] == '-' && j > 0 && out[j-1] == ' ')
            j--;

        out[j++] = s[i++];
        last_space = 0;
    }

    /* Trim trailing space */
    if (j > 0 && out[j-1] == ' ')
        j--;

    out[j] = 0;
    return out;
}



/* Utility: append text to display */
static void chat_display(const char *text)
{
    GtkTextIter end;
    gtk_text_buffer_get_end_iter(chat_text_buffer, &end);
    gtk_text_buffer_insert(chat_text_buffer, &end, text, -1);
    gtk_text_buffer_insert(chat_text_buffer, &end, "\n", -1);

    /* Voice output */
    char cmd[512];
    snprintf(cmd, sizeof(cmd), "espeak \"%s\" &", text);
    system(cmd);
}

static void chat_clear_clicked(GtkButton *button, gpointer user_data)
{
    gtk_text_buffer_set_text(chat_text_buffer, "", -1);
    gtk_widget_show(chat_gif);

}


/* Send button logic */
static void chat_send_clicked(GtkButton *button, gpointer user_data)
{
    const char *input = gtk_entry_get_text(GTK_ENTRY(chat_entry));
    char output[999];

    if (strlen(input) == 0)
        return;

    if (strcmp(input, "hi") == 0)
        strcpy(output, "Hello! How can I help you?");
    else if (strcmp(input, "fuad") == 0)
        strcpy(output, "Fuad Is a boy.");
    else if (strcmp(input, "who are you") == 0)
        strcpy(output, "My name is Taskbot. I am a vatual assitant. My main purpus is to make your life easy");
    else if (strcmp(input, "apps") == 0)
        strcpy(output, "Apps button will open applications.");
    else if (strcmp(input, "apps") == 0)
        strcpy(output, "Apps button will open applications.");
    else if (strcmp(input, "apps") == 0)
        strcpy(output, "Apps button will open applications.");
    else {
    char *raw = ollama_chat_cli(input);
        if (!raw) {
            strcpy(output, "Error: No response from AI.");
        } else {
            char *clean = filter_ai_response(raw);
            strncpy(output, clean, sizeof(output) - 1);
            output[sizeof(output) - 1] = '\0';
            free(clean);
            free(raw);
        }
    }

        

    
    gtk_widget_hide(chat_gif);
    chat_display(output);
    gtk_entry_set_text(GTK_ENTRY(chat_entry), "");
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkWidget *main_grid;
    GtkWidget *left_grid, *right_grid;
    GtkWidget *scroll;
    GtkWidget *bottom_grid;

    GtkWidget *button1, *button2, *button3, *button4;
    GtkWidget *button5, *button6, *button7, *button8;
    GtkWidget *button10;
    GtkWidget *send_btn;
    GtkWidget *clear_btn;
    GtkWidget *overlay;


    /* Window */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Taskbot");
    gtk_window_set_default_size(GTK_WINDOW(window), 550, 300);
    gtk_window_set_resizable(GTK_WINDOW(window), FALSE);

    main_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(main_grid), 10);
    gtk_grid_set_row_spacing(GTK_GRID(main_grid), 10);
    gtk_widget_set_margin_start(main_grid, 10);
    gtk_widget_set_margin_end(main_grid, 10);
    gtk_widget_set_margin_top(main_grid, 10);
    gtk_widget_set_margin_bottom(main_grid, 10);

    gtk_container_add(GTK_CONTAINER(window), main_grid);

    /* LEFT BUTTONS */
    left_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(left_grid), 6);
    gtk_widget_set_margin_start(left_grid, 8);
    gtk_widget_set_margin_end(left_grid, 8);
    gtk_widget_set_margin_top(left_grid, 8);
    gtk_widget_set_margin_bottom(left_grid, 8);
    


    button1  = gtk_button_new_with_label("System Info");
    button2  = gtk_button_new_with_label("Reminder");
    button3  = gtk_button_new_with_label("Timer");
    button4  = gtk_button_new_with_label("Converter");
    button10 = gtk_button_new_with_label("Setting");

    gtk_grid_attach(GTK_GRID(left_grid), button1,  0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(left_grid), button2,  0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(left_grid), button3,  0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(left_grid), button4,  0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(left_grid), button10, 0, 4, 1, 1);

    /* RIGHT BUTTONS */
    right_grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(right_grid), 6);
    gtk_widget_set_margin_start(right_grid, 8);
    gtk_widget_set_margin_end(right_grid, 8);
    gtk_widget_set_margin_top(right_grid, 8);
    gtk_widget_set_margin_bottom(right_grid, 8);


    button6 = gtk_button_new_with_label("Notes");
    button7 = gtk_button_new_with_label("CMD");
    button5 = gtk_button_new_with_label("Apps");
    button8 = gtk_button_new_with_label("SMS");

    gtk_grid_attach(GTK_GRID(right_grid), button6, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(right_grid), button7, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(right_grid), button5, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(right_grid), button8, 0, 3, 1, 1);



    g_signal_connect(button1, "clicked", G_CALLBACK(system_info), app);
    g_signal_connect(button2, "clicked", G_CALLBACK(reminder), app);
    g_signal_connect(button3, "clicked", G_CALLBACK(timer), app);
    g_signal_connect(button4, "clicked", G_CALLBACK(converter), app);
    g_signal_connect(button5, "clicked", G_CALLBACK(apps), app);
    g_signal_connect(button6, "clicked", G_CALLBACK(notes), app);
    g_signal_connect(button7, "clicked", G_CALLBACK(cmd), NULL);
    g_signal_connect(button8, "clicked", G_CALLBACK(sms_start), app);
    // g_signal_connect(button9, "clicked", G_CALLBACK(sms_join), app);
    g_signal_connect(button10, "clicked", G_CALLBACK(setting), app);
    // g_signal_connect(button11, "clicked", G_CALLBACK(setting), app);
    // g_signal_connect(button12, "clicked", G_CALLBACK(setting), app);

    /* TEXT DISPLAY */
    chat_text_view = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(chat_text_view), FALSE);
    gtk_text_view_set_cursor_visible(GTK_TEXT_VIEW(chat_text_view), FALSE);

    chat_text_buffer =
        gtk_text_view_get_buffer(GTK_TEXT_VIEW(chat_text_view));

    

/* Load GIF */
    chat_gif = gtk_image_new_from_file("src/video/eye2.gif");

    /* Overlay container */
    overlay = gtk_overlay_new();
    gtk_widget_set_size_request(overlay, 360, 200);

    /* Scrolled text view */
    scroll = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scroll), chat_text_view);

    /* Add widgets */
        /* Base widget = text */
    gtk_container_add(GTK_CONTAINER(overlay), scroll);

    /* GIF on top */
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), chat_gif);

    /* Center GIF */
    gtk_widget_set_halign(chat_gif, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(chat_gif, GTK_ALIGN_CENTER);

    /* Allow clicks to go through GIF */
    gtk_overlay_set_overlay_pass_through(
        GTK_OVERLAY(overlay), chat_gif, TRUE);


    /* Center GIF */
    gtk_widget_set_halign(chat_gif, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(chat_gif, GTK_ALIGN_CENTER);


    /* BOTTOM INPUT */
    bottom_grid = gtk_grid_new();
    gtk_grid_set_column_spacing(GTK_GRID(bottom_grid), 6);
    gtk_widget_set_margin_top(bottom_grid, 10);
    gtk_widget_set_margin_bottom(bottom_grid, 5);
    gtk_widget_set_margin_start(bottom_grid, 34);

    

    chat_entry = gtk_entry_new();
    gtk_widget_set_size_request(chat_entry, 300, -1);

    clear_btn = gtk_button_new_with_label("Clear");
    send_btn  = gtk_button_new_with_label("Send");

    g_signal_connect(clear_btn, "clicked",
                    G_CALLBACK(chat_clear_clicked), NULL);

    g_signal_connect(send_btn, "clicked",
                    G_CALLBACK(chat_send_clicked), NULL);

    /* Center bottom row */
    gtk_widget_set_halign(bottom_grid, GTK_ALIGN_CENTER);

    gtk_grid_attach(GTK_GRID(bottom_grid), clear_btn, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(bottom_grid), chat_entry, 1, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(bottom_grid), send_btn, 2, 0, 1, 1);


    /* MAIN LAYOUT */
    gtk_grid_attach(GTK_GRID(main_grid), left_grid,  0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(main_grid), overlay, 1, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), right_grid, 2, 0, 1, 1);

    gtk_grid_attach(GTK_GRID(main_grid), bottom_grid, 0, 1, 3, 1);

    gtk_widget_show_all(window);
    
}



gpointer check_reminder_thread(gpointer data)
{
    check_reminder();
    system("./hotkey_calendar");   // your existing loop function
    return NULL;
}


/* ---------------- main ---------------- */

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    /* background tasks */
    g_thread_new("reminder_thread", check_reminder_thread, NULL);
    g_thread_new("hotkey_thread", hotkey_listener_thread, NULL);

    app = gtk_application_new("com.example.taskbot", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}


