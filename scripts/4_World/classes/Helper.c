class AutolockVehicles_Helper
{
    static string EscapeString(string StringToEscape)
    {
        int backslash = 92;
        int quote = 34;

        StringToEscape.Replace("\"", backslash.AsciiToString() + quote.AsciiToString());
        return StringToEscape;
    }

    static string GetTimestamp()
    {
        int year = 0;
        int month = 0;
        int day = 0;
        int hour = 0;
        int minute = 0;
        int second = 0;

        GetHourMinuteSecondUTC(hour, minute, second);
        GetYearMonthDayUTC(year, month, day);

        return year.ToStringLen(4) + "-" + month.ToStringLen(2) + "-" + day.ToStringLen(2) + "T" + hour.ToStringLen(2) + ":" + minute.ToStringLen(2) + ":" + second.ToStringLen(2) + "Z";
    }
}
