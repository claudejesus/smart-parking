

// Google Apps Script to manage parking space data

// Spreadsheet ID (replace with your Google Sheet ID)
const SPREADSHEET_ID = "1XjC9yOebiRO1oPzjDGOCmLDsr2oHZSFguUrPgbjTlEk"; // Replace with your actual spreadsheet ID
const SHEET_NAME = "Sheet1"; // Replace with your sheet name

/**
 * Do Get: Handles GET requests to fetch the available spaces.
 * @param {Object} e - The request parameters.
 * @return {Object} - A JSON response with the available spaces.
 */
function doGet(e) {
  const sheet = SpreadsheetApp.openById(SPREADSHEET_ID).getSheetByName(SHEET_NAME);
  
  if (!sheet) {
    return ContentService.createTextOutput("Sheet not found").setMimeType(ContentService.MimeType.TEXT);
  }
  
  // Assume the available spaces are in cell A2
  const availableSpaces = sheet.getRange("B2").getValue();
  
  return ContentService
    .createTextOutput(availableSpaces.toString())
    .setMimeType(ContentService.MimeType.TEXT);
}

/**
 * Do Post: Handles POST requests to update the available spaces.
 * @param {Object} e - The request parameters.
 * @return {Object} - A JSON response confirming the update.
 */
function doPost(e) {
  const sheet = SpreadsheetApp.openById(SPREADSHEET_ID).getSheetByName(SHEET_NAME);
  
  if (!sheet) {
    return ContentService.createTextOutput("Sheet not found").setMimeType(ContentService.MimeType.TEXT);
  }
  
  try {
    // Get the "spaces" parameter from the POST data
    const spaces = e.parameter.spaces;
    
    if (!spaces) {
      return ContentService
        .createTextOutput("Missing 'spaces' parameter")
        .setMimeType(ContentService.MimeType.TEXT);
    }
    
    // Update the available spaces in cell A2
    sheet.getRange("A2").setValue(parseInt(spaces, 10));
    
    return ContentService
      .createTextOutput("Spaces updated successfully!")
      .setMimeType(ContentService.MimeType.TEXT);
  } catch (error) {
    return ContentService
      .createTextOutput("Error: " + error.message)
      .setMimeType(ContentService.MimeType.TEXT);
  }
}

/**
 * Initialize the sheet with default data (run once to set up).
 */
function initializeSheet() {
  const sheet = SpreadsheetApp.openById(SPREADSHEET_ID).getSheetByName(SHEET_NAME);
  
  if (!sheet) {
    const newSheet = SpreadsheetApp.openById(SPREADSHEET_ID).insertSheet(SHEET_NAME);
    newSheet.getRange("A1").setValue("Available Spaces");
    newSheet.getRange("A2").setValue(10); // Default spaces
  } else {
    sheet.getRange("A1").setValue("Available Spaces");
    sheet.getRange("A2").setValue(10); // Default spaces
  }
}
